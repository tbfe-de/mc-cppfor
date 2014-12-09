#ifdef SEPARATE_MODULE
bool notNullFunction(int v) {
	return (v != 0);
}

struct NotNullFunctor {
	bool operator()(int v) const;
};

bool NotNullFunctor::operator()(int v) const {
	return (v != 0);
}
#endif
