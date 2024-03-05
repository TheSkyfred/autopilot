Mode *Plane::mode_from_mode_num(const enum Mode::Number num)
{
    Mode *ret = nullptr;
    switch (num) {
            case Mode::Number::INITIALISING:
        ret = &mode_Initializing;
        break;
            case Mode::Number::TAKEOFF:
        ret = &mode_Takeoff;
        break;
    case Mode::Number::CIRCLE:
        ret = &mode_Circle;
        break;
    case Mode::Number::STABILIZE:
        ret = &mode_Stabilize;
        break;
    case Mode::Number::CRUISE:
        ret = &mode_cruise;
        break;
            case Mode::Number::LANDING:
        ret = &mode_Landing;
        break;



    }
    return ret;
}