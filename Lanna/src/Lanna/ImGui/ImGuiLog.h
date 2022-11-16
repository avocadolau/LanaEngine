#pragma once

#include "imgui.h"

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



