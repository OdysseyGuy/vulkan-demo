#include <string>

class RenderPass {};

class RenderGraph {
public:
    void Compile();
    void Execute();

    RenderPass& AddPass(const std::string& PassName);
};