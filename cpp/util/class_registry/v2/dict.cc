#include "dict.h"

Registry<Dict>* GlobalDictRegistry() {
    static Registry<Dict>* kr = new Registry<Dict>;
    return kr;
}

REGISTER_PLUGIN_KERNEL_SIMPLE("TFDict",TFDict);
REGISTER_PLUGIN_KERNEL_SIMPLE("TorchDict",TorchDict);
