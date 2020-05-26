#include <core/deepreader.hpp>

DeepReader::DeepReader(const QString& cfg)
    : Command(), cpu(Processor()), config(cfg) {}

DeepReader::~DeepReader() {}