#pragma once

#include "imgui.h"

//#define LOG_PABLO

#ifndef LOG_PABLO



struct ImGuiLog
{
    enum LogLevel {
        TRACE,
        INFO,
        WARN,
        ERR,
        FATAL,
        TOTAL
    };

    struct Log
    {
        const char* text;
        LogLevel loglvl;
        Log(const char* _text,LogLevel _loglvl): text(_text), loglvl(_loglvl) {}
    };

    bool clear;
    bool autoScroll;
    unsigned int offset = 0;

    ImVec4 LevelColors[LogLevel::TOTAL];
    bool filters[LogLevel::TOTAL] = { true };
    std::list<Log*> logs;

    ImGuiLog()
    {
        autoScroll = true;
        Update();

        LevelColors[LogLevel::TRACE] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        LevelColors[LogLevel::INFO] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::WARN] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::ERR] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::FATAL] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    void Update()
    {
        //Buf.clear();
        offset = 0;
        logs.clear();
        clear = false;
    }

    void AddLog(LogLevel level, const char* fmt)
    {

        logs.push_back(new Log(fmt, level));
    }

    void Draw(const char* title, bool* p_open = NULL)
    {

        ImGui::Begin(title, p_open, ImGuiWindowFlags_MenuBar);
        // Options menu
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                ImGui::Checkbox("Auto-scroll", &autoScroll);
                ImGui::Checkbox("TRACE", &filters[TRACE]);
                ImGui::Checkbox("INFO", &filters[INFO]);
                ImGui::Checkbox("ERROR", &filters[ERR]);
                ImGui::Checkbox("FATAL", &filters[FATAL]);

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (ImGui::Button("Clear"))
            clear = true;

        

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (clear)
            Update();

        for (auto l : logs)
        {
            if (filters[l->loglvl])
                ImGui::TextColored(LevelColors[l->loglvl], l->text);
        }
        if (autoScroll)
        {
            if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxX())
                ImGui::SetScrollHereY(1.0f);
        }


        ImGui::EndChild();
        ImGui::End();
    }

};

#endif // !LOG_PABLO

#ifdef LOG_PABLO

struct ImGuiLog
{
    enum LogLevel {
        TRACE,
        INFO,
        WARN,
        ERR,
        FATAL,
        LAST
    };

    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    ImVector<LogLevel>  LogLevels;
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

    ImVec4 LevelColors[LogLevel::LAST];

    ImGuiLog()
    {
        AutoScroll = true;
        Clear();

        LevelColors[LogLevel::TRACE] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        LevelColors[LogLevel::INFO] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::WARN] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::ERR] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
        LevelColors[LogLevel::FATAL] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    void    Clear()
    {
        Buf.clear();
        LogLevels.clear();
        LineOffsets.clear();

        LineOffsets.push_back(0);
    }

    void    AddLog(LogLevel level, const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n') {
                LineOffsets.push_back(old_size + 1);
                LogLevels.push_back(level);
            }
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        if (Buf.size() > 0) {

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have random access to the result of our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end)) {
                        ImGui::PushStyleColor(ImGuiCol_Text, LevelColors[LogLevels[line_no]]);
                        ImGui::TextUnformatted(line_start, line_end);
                        ImGui::PopStyleColor();
                    }
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   ImGui::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using ImGuiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we have an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size - 1);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        ImGui::PushStyleColor(ImGuiCol_Text, LevelColors[LogLevels[line_no]]);
                        ImGui::TextUnformatted(line_start, line_end);
                        ImGui::PopStyleColor();
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }
};


#endif