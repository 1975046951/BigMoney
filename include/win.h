#pragma once
#include "port.h"
#include "msg.h"

namespace BigMoney {
class Window : public MsgReactor{
public:
    Window(int x = 0, int y = 0, int startx = 0, int starty = 0)
        : x_(x),
          y_(y),
          startx_(startx),
          starty_(starty) {
              win_ = newwin(y_, x_, starty_, startx_);
    }
    bool MessageProc(const Msg &msg) override {
        if (msg.msg_type == kPaint) {
            if (static_cast<Window*>(msg.data) == this) {
                Paint();
                return true;
            }
        }
        return false;
    }
    void Update() {
        Msg msg;
        msg.msg_type = kPaint;
        msg.data = static_cast<void*>(this);
        PostMessage(msg);
    }
    virtual void Paint() {

    };
    virtual ~Window() {
        if (win_) {
            delwin(win_);
        }
    }

protected:
    WINDOW *win_{nullptr};
    int x_;
    int y_;
    int startx_;
    int starty_;
};
} // namespace BigMoney