template<class I, class O>
class ne {
public:
  typedef O (*activate)(I);

  std::vector<double> weights;

  activate f;
  ne(activate f) : f(f) {};
  ~ne() {};
};
