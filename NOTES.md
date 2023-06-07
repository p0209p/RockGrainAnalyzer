# OpenCL Notes

## Global Dimensions
## Local Dimensions
## Kernel Function
## OpenCL Context
    For two devices (for example a CPU and a GPU) to share data, they must be in the same context.
## Command Queues
    All the command are added to a queue for each device

## Memory Model
    1. The data must be transferred from the host memory to the global memory. If there are multiple devices, we need to transfer
    to each one. This is slow !
    2 .Once the data is transferred to the global memory, we need to write routines to get relevant data into the local memory of each compute unit.

## Typical Workflow
    1. Get devices, create a context
    2. Create command queue
    3. Create a program
    4. Build the program
    5. Create the kernels
    6. Create memory objects
    7. Enqueue writes to copy data
    8. Set the kernel arguments
    9. Enqueue kernel executions
    10. Enqueue reads to copy data back to cpu
    11. Wait for command to finish // Why this ? Because OpenCL is asynchronous