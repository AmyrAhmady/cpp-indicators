/*
*   cpp-indicators - iAmir (Amir Ahmady) (C) 2020
*       file name: indicators.hpp
*/

#ifndef __CPP_INDICATORS_
#define __CPP_INDICATORS_

#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>

namespace indicator
{

using namespace std::chrono;

std::vector<std::vector<std::string>> IndicatorFrames = {
    {"|", "/", "-", "\\"},
    {"+", "x"},
    {"v", "<", "^", ">"},
    {"( o    )", "(  o   )", "(   o  )", "(    o )", "(     o)", "(    o )", "(   o  )", "(  o   )", "( o    )"},
    {">))'>    ", " >))'>   ", "  >))'>  ", "   >))'> ", "    >))'>", "    <'((<", "   <'((< ", "  <'((<  ", " <'((<   ", "<'((<    "},
    {"  o o o o o", "o   o o o o", "o o   o o o", "o o o   o o", "o o o o   o", "o o o o o  ", "o o o o o o"},
    {"::|\\____________::", "::_|\\___________::", "::__|\\__________::", "::___|\\_________::", "::____|\\________::", "::_____|\\_______::", "::______|\\______::", "::_______|\\_____::", "::________|\\____::", "::_________|\\___::", "::__________|\\__::", "::___________|\\_::", "::____________|\\::", "::____________/|::", "::___________/|_::", "::__________/|__::", "::_________/|___::", "::________/|____::", "::_______/|_____::", "::______/|______::", "::_____/|_______::", "::____/|________::", "::___/|_________::", "::__/|__________::", "::_/|___________::", "::/|____________::"},
};

class indicator
{
public:
    indicator(const duration<int, std::milli> &delay = 200ms,
              int type = 0,
              const std::string &endmsg = "",
              const std::string &prefix = "",
              const std::string &suffix = "",
              bool hide_on_end = false,
              const std::vector<std::string> &custom_frames = {}) : frame_delay(delay),
                                                                    type(type),
                                                                    endmsg(endmsg),
                                                                    prefix(prefix),
                                                                    suffix(suffix),
                                                                    hide_on_end(hide_on_end),
                                                                    custom_frames(custom_frames),
                                                                    is_active(false)
    {
    }

    ~indicator()
    {
        stop();
    }

    void start()
    {
        is_active = true;
        std::cout.flush();
        last_text_size = 0;

        thread = std::thread([&]() {
            int c = -1;
            std::vector<std::string> frames;
            if (custom_frames.size() > 0)
                frames = custom_frames;
            else
                frames = IndicatorFrames[type];
            int l = frames.size();

            while (is_active)
            {
                std::string frame = frames[c = ++c % l];
                std::cout << "\r" << prefix << frame << suffix;
                last_text_size = prefix.length() + frame.length() + suffix.length();
                std::cout.flush();
                std::this_thread::sleep_for(frame_delay);
            }
        });
    }

    void stop()
    {
        if (is_active)
        {
            is_active = false;
            thread.join();
            if (endmsg.size() > 0)
            {
                if (hide_on_end)
                {
                    std::cout << "\r" << std::string(last_text_size, ' ');
                    std::cout << "\r"
                              << " - " << endmsg << std::endl;
                }
                else
                {
                    std::cout << "\n"
                              << " - " << endmsg << std::endl;
                }
            }
            std::cout.flush();
        }
    }

    void set_frame_delay(const duration<int, std::milli> &delay)
    {
        frame_delay = delay;
    }

    void set_prefix(const std::string &string)
    {
        prefix = string;
    }

    void set_suffix(const std::string &string)
    {
        suffix = string;
    }

    void set_end_msg(const std::string &string)
    {
        endmsg = string;
    }

private:
    duration<int, std::milli> frame_delay;
    std::string prefix;
    std::string suffix;
    std::vector<std::string> custom_frames;
    int type;
    std::string endmsg;
    int last_text_size;
    bool hide_on_end;
    bool is_active;
    std::mutex lock;
    std::thread thread;
};
} // namespace indicator

#endif