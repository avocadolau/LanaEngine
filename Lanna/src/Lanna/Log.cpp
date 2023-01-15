#include "lnpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "imgui.h"

namespace Lanna {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<Console> Log::s_ClientLogger;
    Console* Console::console_Instance;
	//std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("LANNA");
		s_CoreLogger->set_level(spdlog::level::trace);
	}

	const char* Log::GetCoreLastLog()
	{
		return nullptr;
	}

	Console::Console()
	{
		ClearLog();
		memset(InputBuf, 0, sizeof(InputBuf));
		AutoScroll = true;
		ScrollToBottom = false; 
        LN_CORE_TRACE("console initialized");
	}

	Console::~Console()
	{
		ClearLog();
	}

    void Console::Init()
    {
        Items.clear();
        console_Instance = this;
    }

	void Console::ClearLog()
	{
		for (int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
	}

    void Console::AddLog(LogLevel logLevel, const char* fmt,...) IM_FMTARGS(2)
    {
        if (fmt!="{0}")
        {
            std::string level;
            switch (logLevel)
            {
            case LogLevel::INFO:        level = "[info] ";          break;
            case LogLevel::WARN:        level = "[warn] ";          break;
            case LogLevel::ERR:         level = "[error] ";         break;
            case LogLevel::FATAL:       level = "[fatal] ";         break;
            case LogLevel::TRACE:       level = "[trace] ";         break;
            }

            std::string text;
            text = level + fmt;
            

            // FIXME-OPT
            char buf[1024];
            va_list args;
            va_start(args, text);
            vsnprintf(buf, IM_ARRAYSIZE(buf), text.c_str(), args);
            buf[IM_ARRAYSIZE(buf) - 1] = 0;
            va_end(args);


            Items.push_back(Strdup(buf));
        }
    }

    void Console::Render(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close Console"))
                *p_open = false;
            ImGui::EndPopup();
        }

        ImGui::TextWrapped(
            "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
            "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
        ImGui::TextWrapped("Enter 'HELP' for help.");

        // TODO: display items starting from the bottom

        if (ImGui::SmallButton("Add Debug Text")) {
            LN_INFO("info example");
            LN_TRACE("trace example");
            LN_WARN("warn example");
            LN_ERROR("error example");
            LN_CRITICAL("critical example");
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) { ClearLog(); }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy");
        //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

        ImGui::Separator();

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Options, Filter
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        Filter.Render("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets.
        // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        // to only process visible items. The clipper will automatically measure the height of your first item and then
        // "seek" to display only items in the visible area.
        // To use the clipper we can replace your standard loop:
        //      for (int i = 0; i < Items.Size; i++)
        //   With:
        //      ImGuiListClipper clipper;
        //      clipper.Begin(Items.Size);
        //      while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // - That your items are evenly spaced (same height)
        // - That you have cheap random access to your elements (you can access them given their index,
        //   without processing all the ones before)
        // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        // We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        // to improve this example code!
        // If your items are of variable height:
        // - Split them into same height items would be simpler and facilitate random-seeking into your list.
        // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!Filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strstr(item, "[info]")) { color = ImVec4(1.0f, 1.0f, 1.0f, 0.9f); has_color = true; }
            else if (strstr(item, "[warn]")) { color = ImVec4(1.0f, 0.8f, 0.3f, 0.8f); has_color = true; }
            else if (strstr(item, "[fatal]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strstr(item, "[trace]")) { color = ImVec4(1.0f, 0.9f, 0.76f, 1.0f); has_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        ScrollToBottom = false;

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();

        ImGui::End();
    }

}