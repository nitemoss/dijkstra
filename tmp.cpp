




if(current_vertex == to){
    cout << "Destination reached, tracing way back..." << endl;
    vertex* backtrace_iterator = to;
    if(backtrace_iterator->previous == NULL){
        cout << "No path back found" << endl;
        return;
    }
    while(backtrace_iterator->previous != NULL){
        cout << backtrace_iterator->name;
        backtrace_iterator = backtrace_iterator->previous;
    }

    return;
}





