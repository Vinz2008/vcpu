
struct Load {
    
};

struct Store {
    
};

struct Cmp {

};

struct Jmp {

};

struct Math {

};

struct Misc  {
    enum {
        noop,
        halt
    } type;
};

struct Instruction {
    enum {
        load,
        store,
        cmp,
        jmp,
        math,
        misc
    } type;
    union {
        struct Load* l;
        struct Store* s;
        struct Cmp* c;
        struct Jmp* j;
        struct Math* m;
        struct Misc* mi;
    } val;
}