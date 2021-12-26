
#include <MCPPin.h>
#include <Weiche.h>
#ifdef __Weiche__
Weiche weiche[NUMBERWEICHEN];
#define __WEICHE__
#endif
#ifdef __MCPPIN__
MCPPin mcppin;
#define __MCPPIN__
#endif
