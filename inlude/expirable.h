class Expirable {
public:
    virtual ~Expirable() = default;
    virtual bool isexpired() const = 0;
};
