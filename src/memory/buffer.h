


#ifndef _SMILE_MEMORY_BUFFER_H_
#define _SMILE_MEMORY_BUFFER_H_ 

#include "memory/types.h"

class BufferPool;

class Buffer {
  public:
    Buffer( BufferPool* m_pool ) noexcept;
    ~Buffer() noexcept;

    void write(char* data, uint32_t numBytes, uint32_t startByte );

    void read(char* data, uint32_t numBytes, uint32_t startByte ) const ;

  private:

    char*           m_shadow;
    bufferId_t      m_bId;
    transactionId_t m_tId;
    // falta punter a la estructura interna de la buffer pool
};

#endif /* ifndef _SMILE_MEMORY_BUFFER_H_ */
