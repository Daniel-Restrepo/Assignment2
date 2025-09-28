// convert.c

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// turns a number into a 32-char binary
static void to_32bit_binary(uint32_t value, char *out) {
    for (int i = 31; i >= 0; --i) {
        out[31 - i] = ((value >> i) & 1u) ? '1' : '0';
    }
    out[32] = '\0';
}

// turns a small number between 0-15 into a single hex digit
static char nibble_to_hex(int v) {
    return (v < 10) ? (char)('0' + v) : (char)('A' + (v - 10));
}

// turns an octal number into binary
void oct_to_bin(const char *oct, char *out) {
    static const char *map3[8] = {
        "000","001","010","011","100","101","110","111"
    };

    int pos = 0;  // how many chars written into out

    for (const char *p = oct; *p; ++p) {
        char c = *p;

        // input is assumed valid in tests; if not, write empty and return
        if (c < '0' || c > '7') {
            out[0] = '\0';
            return;
        }

        const char *t = map3[c - '0'];
        out[pos++] = t[0];
        out[pos++] = t[1];
        out[pos++] = t[2];
    }

    out[pos] = '\0';
}

// converts octal to binary and then to hex.
// also pads binary so it lines up into groups of 4
void oct_to_hex(const char *oct, char *out) {

    // converts oct into bin
    char bin[512];
    oct_to_bin(oct, bin);

    if (bin[0] == '\0') {
        out[0] = '\0';
        return;
    }

    // pads binary to multiples of 4
    int len = (int)strlen(bin);
    int pad = (4 - (len % 4)) % 4;

    char padded[520];
    int pos = 0;

    for (int i = 0; i < pad; ++i) {
        padded[pos++] = '0';
    }

    memcpy(padded + pos, bin, (size_t)len);
    pos += len;
    padded[pos] = '\0';

    // converts the multiples of 4 into hex
    char hex[520];
    int hpos = 0;

    for (int i = 0; i < pos; i += 4) {
        int v = (padded[i]   - '0') * 8
              + (padded[i+1] - '0') * 4
              + (padded[i+2] - '0') * 2
              + (padded[i+3] - '0');
        hex[hpos++] = nibble_to_hex(v);
    }

    hex[hpos] = '\0';

    // strips the leading zeros (keeps one 0 if all zeros)
    int lead = 0;
    while (hex[lead] == '0' && hex[lead + 1] != '\0') {
        lead++;
    }

    strcpy(out, hex + lead);
}

// turns hex into binary
void hex_to_bin(const char *hex, char *out) {
    static const char *map4[16] = {
        "0000","0001","0010","0011",
        "0100","0101","0110","0111",
        "1000","1001","1010","1011",
        "1100","1101","1110","1111"
    };

    int pos = 0;

    for (const char *p = hex; *p; ++p) {
        unsigned char c = (unsigned char)*p;
        int v;

        if (c >= '0' && c <= '9') {
            v = c - '0';
        }
        else if (c >= 'A' && c <= 'F') {
            v = 10 + (c - 'A');
        }
        else if (c >= 'a' && c <= 'f') {
            v = 10 + (c - 'a');
        }
        else {
            out[0] = '\0';
            return;
        }

        const char *q = map4[v];
        out[pos++] = q[0];
        out[pos++] = q[1];
        out[pos++] = q[2];
        out[pos++] = q[3];
    }

    out[pos] = '\0';
}

// shows a number using sign-magnitude format
void to_sign_magnitude(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
        return;
    }

    // if n is negative, take abs value safely, then keep lower 31 bits
    uint32_t mag = (uint32_t)((-(int64_t)n) & 0x7FFFFFFF);

    out[0] = '1';  // sign bit

    for (int bit = 30; bit >= 0; --bit) {
        out[31 - bit] = ((mag >> bit) & 1u) ? '1' : '0';
    }

    out[32] = '\0';
}

// shows a number using one’s complement format
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_32bit_binary((uint32_t)n, out);
        return;
    }

    uint32_t pos = (uint32_t)(-(int64_t)n);  // abs value
    to_32bit_binary(~pos, out);             // flip every bit
}

// shows a number using two’s complement format
void to_twos_complement(int32_t n, char *out) {
    to_32bit_binary((uint32_t)n, out);
}