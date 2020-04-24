template <typename T>
std::vector<T> load(std::string filename, T(*parse)(std::string))
{
  std::vector<T> v;

  std::ifstream afile(filename, std::ios::in);
  if (afile.is_open()) {
    std::string line;
    while (std::getline(afile, line)) {
      try {
        v.push_back( parse(line) );
      } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
      }
    }
    afile.close();
  }
  else {
    std::cerr << "Unable to open file:" << filename << std::endl;
  }

  return v;
}
