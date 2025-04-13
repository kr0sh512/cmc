enum
{
    MY_INT_MAX = ~0u >> (!0),
    MY_INT_MIN = ~(~0u >> (!0))
};

int
satsum(int v1, int v2)
{
    if (v1 > 0 && (signed int) MY_INT_MAX - v1 < v2) {
        return MY_INT_MAX;
    }

    if (v1 < 0 && (signed int) MY_INT_MIN - v1 > v2) {
        return MY_INT_MIN;
    }

    return v1 + v2;
}
