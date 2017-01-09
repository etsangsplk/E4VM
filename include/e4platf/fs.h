/* * This is an open source non-commercial project. Dear PVS-Studio, please check it.
 * PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
 */

#pragma once

#include <stdio.h>
#include "e4platf/types.h"

namespace e4 {

#if E4FEATURE_FS
class File {
private:
    FILE *f_ = nullptr;
public:
    explicit File(const char *fn, const char *mode) {
        f_ = ::fopen(fn, mode);
        G_ASSERT(is_open());
    }
    ~File() {
        close();
    }
    bool is_open() const {
        return f_ != nullptr;
    }
    void close() {
        if (f_) {
            ::fclose(f_);
        }
        f_ = nullptr;
    }

    static Vector<Uint8> read_file(const char *fn) {
        File f(fn, "rb");
        return f.read_file();
    }

    Vector<Uint8> read_file() {
        ::fseek(f_, 0, SEEK_END);
        Count size = static_cast<Count>(::ftell(f_));

        Vector<Uint8> result;
        result.resize(size);

        ::fseek(f_, 0, SEEK_SET);
        ::fread(result.data(), size, 1, f_);
        return result;
    }
}; // class File
#endif // E4FEATURE_FS

} // ns e4

