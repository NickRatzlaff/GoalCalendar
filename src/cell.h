#include <FastLED.h>

enum class Status {
    Success,
    Failure,
    Pending,
    NotIncluded,
    Inactive
};

class Cell {
    public:
        int ledNums[4];
        Cell(int a, int b, int c, int d, Status status=Status::Inactive);
        Status status = Status::NotIncluded;
        CRGB::HTMLColorCode statusColor();
};