#include "number.h"

uint2022_t from_uint(uint32_t i) {
    uint2022_t res;

    for (int j = 0; j < 68; j++) {
        res.digits[j] = 0;
    }

    if (i == 0) {
        res.digits[0] = 0;
        res.sizeOfDigits = 1;
    }
    else {
        int j = 0;
        int cnt = 0;
        while (i != 0) {
            res.digits[j] = (i % res.base);
            i /= res.base;
            cnt++;
            j++;
        }
        res.sizeOfDigits = cnt;
    }
    return res;
}

uint2022_t from_string(const char* buff) {
    uint2022_t res;
    std::string bf = std::string(buff);
    std::string ref = "481560916771158684800786922703235625631274322714142263414417884163925873322306437689024231009526751394401758326916367106052034484602375642882110959089521812209947069992139877256008949136579813164413834190131240610432508865633901300457687591589632190325582710683886781973951695733384278544896131740867054246692573031629150247882082682647773168904426336814855367810693467547461780797071163567159452928068892906992787178135839959347223507647240845924670958716173279750751341651541295792537288393481542519773223140547524361834615428274169543954961376881442030303829940191406452725012875774576546969913778507874303";

    for (int j = 0; j < 68; j++) {
        res.digits[j] = 0;
    }

    if (bf.length() == ref.length()) {
        for (int i = 0; i < bf.length(); i++) {
            if ((bf[i] - '0') > (ref[i] - '0')) {
                throw std::invalid_argument("Undefined Behavior");
            }
        }
    }

    int j = 0;
    int cnt = 0;

    for (int i = bf.length(); i > 0; i -= 9) {
        if (i < 9) {
            res.digits[j] = (atoi(bf.substr(0, i).c_str()));
        }
        else {
            res.digits[j] = (atoi(bf.substr(i - 9, 9).c_str()));
        }
        cnt++;
        j++;
    }

    res.sizeOfDigits = cnt;
    return res;
}

bool checkLimit(const uint2022_t& n) {
    const char* ref = "481560916771158684800786922703235625631274322714142263414417884163925873322306437689024231009526751394401758326916367106052034484602375642882110959089521812209947069992139877256008949136579813164413834190131240610432508865633901300457687591589632190325582710683886781973951695733384278544896131740867054246692573031629150247882082682647773168904426336814855367810693467547461780797071163567159452928068892906992787178135839959347223507647240845924670958716173279750751341651541295792537288393481542519773223140547524361834615428274169543954961376881442030303829940191406452725012875774576546969913778507874303";
    uint2022_t r = from_string(ref);

    if (n < r) {
        return true;
    }
    else {
        return false;
    }
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    int flag = 0;
    uint2022_t res = lhs;

    for (int i = 0; i < std::max(lhs.sizeOfDigits, rhs.sizeOfDigits) || flag; i++) {
        if (i == res.sizeOfDigits) {
            res.sizeOfDigits++;
            res.digits[res.sizeOfDigits - 1] = 0;
        }

        if (i < rhs.sizeOfDigits) {
            res.digits[i] += rhs.digits[i] + flag;
        }
        else {
            res.digits[i] += flag;
        }

        if (res.digits[i] >= res.base) {
            res.digits[i] -= res.base;
            flag = 1;
        }
        else {
            flag = 0;
        }
    }

    while ((res.sizeOfDigits > 1) && (res.digits[res.sizeOfDigits - 1] == 0)) {
        res.digits[res.sizeOfDigits - 1] = 0;
        res.sizeOfDigits--;
    }
    if (checkLimit(res) == false) {
        throw std::invalid_argument("Undefined Behavior");
    }
    return res;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res = lhs;

    if (lhs < rhs) {
        throw std::invalid_argument("You have entered incorrect values");
    }
    for (int i = 0; i < res.sizeOfDigits; i++) {
        if (i < rhs.sizeOfDigits) {
            res.digits[i] -= rhs.digits[i];
        }
        if (res.digits[i] < 0) {
            res.digits[i] += res.base;
            res.digits[i + 1]--;
        }
    }

    while ((res.sizeOfDigits > 1) && (res.digits[res.sizeOfDigits - 1] == 0)) {
        res.digits[res.sizeOfDigits - 1] = 0;
        res.sizeOfDigits--;
    }
    return res;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res;

    for (int j = 0; j < 68; j++) {
        res.digits[j] = 0;
    }

    res.sizeOfDigits = (lhs.sizeOfDigits + rhs.sizeOfDigits);
    for (int i = 0; i < lhs.sizeOfDigits; i++) {
        long long flag = 0;
        for (int j = 0; j < rhs.sizeOfDigits || flag; j++) {
            long long tmp = 0;
            if (j < rhs.sizeOfDigits) {
                tmp = (long long)res.digits[i + j] + (long long)lhs.digits[i] * (long long)rhs.digits[j] + flag;
                flag = tmp / res.base;
                tmp -= flag * res.base;
                res.digits[i + j] = tmp;
            }
            else {
                tmp = res.digits[i + j] + flag;
                flag = tmp / res.base;
                tmp -= flag * res.base;
                res.digits[i + j] = tmp;
            }
        }
    }

    while ((res.sizeOfDigits > 1) && (res.digits[res.sizeOfDigits - 1] == 0)) {
        res.digits[res.sizeOfDigits - 1] = 0;
        res.sizeOfDigits--;
    }
    if (checkLimit(res) == false) {
        throw std::invalid_argument("Undefined Behavior");
    }
    return res;
}

/*uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}*/

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs.sizeOfDigits != rhs.sizeOfDigits) {
        return false;
    }
    for (int i = 0; i < lhs.sizeOfDigits; i++) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs == rhs) {
        return false;
    }
    if (lhs.sizeOfDigits == rhs.sizeOfDigits) {
        for (int i = static_cast<int>(lhs.sizeOfDigits) - 1; i >= 0; i--) {
            if (lhs.digits[i] != rhs.digits[i]) {
                return lhs.digits[i] < rhs.digits[i];
            }
        }
        return false;
    }
    else {
        return lhs.sizeOfDigits < rhs.sizeOfDigits;
    }
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    stream << value.digits[value.sizeOfDigits - 1];
    for (int i = value.sizeOfDigits - 2; i >= 0; i--) {
        stream << std::setfill('0') << std::setw(9) << value.digits[i];
    }
    return stream;
}