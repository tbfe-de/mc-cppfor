#include <iostream>

#if !defined(Value_IO_H) && defined(Value_H)
#define Value_IO_h
inline
std::ostream& operator<<(std::ostream& lhs, const Value& rhs) {
	return lhs << "= " << rhs.getValue();
}
#endif

#if !defined(Average_IO_H) && defined(Average_H)
#define Average_IO_h
inline
std::ostream& operator<<(std::ostream& lhs, const Average& rhs) {
	return lhs << "ø " << rhs.getAverage();
}
#endif

#if !defined(Extrema_IO_H) && defined(Extrema_H)
#define Extrema_IO_h
inline
std::ostream& operator<<(std::ostream& lhs, const Extrema& rhs) {
	return lhs << rhs.getMinimum() << " … "
		   << rhs.getMaximum();
}
#endif

#if !defined(Statistic_IO_H) && defined(Statistic_H)
#define Statistic_IO_h
inline
std::ostream& operator<<(std::ostream& lhs, const Statistic& rhs) {
	return lhs << "ø " << rhs.getAverage()
		   << "; " << rhs.getMinimum() << " … "
			   << rhs.getMaximum();
}
#endif
