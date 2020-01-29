#include <errno.h>
#include "slow/io.h"

int read_stream(FILE *f, char **data, size_t *size)
{
    #define CHUNK_SIZE 512
    size_t readsz, totalsz = 0, memsz;
    char *buf, *tmpbuf;
    int ret = 0;
    clearerr(f);
    memsz = CHUNK_SIZE;
    buf = malloc(memsz);
    if (buf != NULL) {
        while (ret == 0) {
            readsz = fread(buf + totalsz, 1, CHUNK_SIZE, f);
            if (ferror(f)) {
                ret = errno;
            } else {
                totalsz += readsz;
                if (totalsz >= memsz) {
                    memsz += CHUNK_SIZE;
                    tmpbuf = realloc(buf, memsz);
                    if (tmpbuf == NULL) {
                        ret = errno;
                    } else
                        buf = tmpbuf;
                }
            }
            if (readsz != CHUNK_SIZE)
                break;
        }
    } else
        ret = errno;
    fclose(f);
    if (ret) {
        free(buf);
        return ret;
    }
    *data = buf;
    *size = totalsz;
    return 0;
}
