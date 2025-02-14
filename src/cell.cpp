#include "cell.h"

Cell::Cell(int a, int b, int c, int d, Status _status) {
    ledNums[0] = a;
    ledNums[1] = b;
    ledNums[2] = c;
    ledNums[3] = d;

    status = _status;
}

CRGB::HTMLColorCode Cell::statusColor() {
    switch (status) {
        case Status::Inactive:
            return CRGB::Black;
            break;
        case Status::Success:
            return CRGB::Green;
            break;
        case Status::Failure:
            return CRGB::Red;
            break;
        case Status::Pending:
            return CRGB::Yellow;
            break;
        case Status::NotIncluded:
            return CRGB::Blue;
            break;
        default:
            return CRGB::MediumTurquoise;
    }
}