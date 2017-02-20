

#ifndef _SMILE_MACROS_H_


#define SMILE_NS_BEGIN namespace smile {
#define SMILE_NS_END }

#define SMILE_NON_COPYABLE( classname ) classname( const classname& ) = delete; \
                                        classname& operator=(const classname& ) = delete;

#endif
