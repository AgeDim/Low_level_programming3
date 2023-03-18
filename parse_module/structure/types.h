#ifndef LOW_LEVEL_PROGRAMMING3_TYPES_H
#define LOW_LEVEL_PROGRAMMING3_TYPES_H
union types {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & string;
        ar & integer;
        ar & boolean;
        ar & real;
    }
public:
    field *string;
    int64_t integer;
    int64_t boolean;
    double real;

};

#endif //LOW_LEVEL_PROGRAMMING3_TYPES_H
