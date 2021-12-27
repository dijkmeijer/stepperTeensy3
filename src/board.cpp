#include "board.hpp"

uint8_t initMCP(){
  mcp1.begin(MCP_1_ADRESS);  // enable motor bord A 1..4 + 4 GPIO
  mcp2.begin(MCP_2_ADRESS);  // 8 GPIO
  mcp3.begin(MCP_3_ADRESS);  // enable motor bord B 1..4 + 4 GPIO
  mcp4.begin(MCP_4_ADRESS);  // 8 GPIO
  return 0;
}