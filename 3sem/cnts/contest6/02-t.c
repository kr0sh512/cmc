long long
stlen(char *buf)
{
    long long i = 0;
    for (; buf[i] != '\0'; ++i) {
    }
    return i;
}

long long
shift(char *buf, long long st, long long sh, long long len)
{
    long long i = st;
    if (i + sh > len) {
        return len;
    }
    for (; i + sh <= len; ++i) {
        buf[i] = buf[i + sh];
    }
    return len - sh;
}

void
normalize_path(char *buf)
{
    long long len = stlen(buf);
    for (int i = 1; buf[i]; ++i) {
        if (buf[i] == '.' && buf[i - 1] == '/') {
            if (buf[i + 1] == '.' && (buf[i + 2] == '/' buf[i + 2] == '\0')) {
                if (i - 2 >= 0) {
                    int j;
                    for (j = i - 2; buf[j] != '/'; --j) {
                    }
                    ++j;
                    if (buf[i + 2] == '/') {
                        len = shift(buf, j, i + 3 - j, len);
                        i = j - 1;
                    } else if (!buf[i + 2]) {
                        len = shift(buf, j, i + 2 - j, len);
                        i = j - 1;
                    }
                } else {
                    if (buf[i + 2] == '/') {
                        len = shift(buf, i, 3, len);
                        --i;
                    } else if (!buf[i + 2]) {
                        len = shift(buf, i, 2, len);
                        --i;
                    }
                }
            } else if (buf[i + 1] == '/' buf[i + 1] == '\0') {
                if (buf[i + 1] == '/') {
                    len = shift(buf, i, 2, len);
                    --i;
                } else if (!buf[i + 1]) {
                    len = shift(buf, i, 1, len);
                    --i;
                }
            }
        }
    }
    len = stlen(buf);
    if (len != 1) {
        if (buf[len - 1] == '/') {
            buf[len - 1] = '\0';
        }
    }
}
