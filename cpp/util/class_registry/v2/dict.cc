#include "dict.h"

KernelRegistry<Dict>* GlobalDictRegistry() {
    static KernelRegistry<Dict>* kr = new KernelRegistry<Dict>;
    return kr;
}

REGISTER_PLUGIN_KERNEL_SIMPLE("TFDict",TFDict);
REGISTER_PLUGIN_KERNEL_SIMPLE("TorchDict",TorchDict);
