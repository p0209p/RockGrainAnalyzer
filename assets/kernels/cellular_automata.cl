kernel void cellular_automata(global float *data) {
    int id = get_global_id(0);
    data[id] = sin(data[id]);
}