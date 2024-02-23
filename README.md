    bitRT is an ultra-high performance ray tracing core library (currently only providing ray traversal acceleration structure and triangle mesh intersection function),
based on non BVH technology routes, with a lot of innovation at the algorithm level.

    The current version has been highly optimized for the AVX2 and AVX512 ISA, and its performance in diffuse ray traversal & intersection is much higher than that the embree.
    
    We will also increase support for GPUs in the future.
    
    The goal of bitRT is to achieve performance comparable to hardware ray tracing through algorithmic innovation and highly optimized software on general-purpose processors(CPU and the general computing unit of GPU)