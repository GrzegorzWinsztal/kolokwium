#include "coordinator.h"
#include "agent.h"

int main() {
    start_agents(4);  // Gamma, Beta, Alpha, Delta
    agent_task();
    return 0;
}
