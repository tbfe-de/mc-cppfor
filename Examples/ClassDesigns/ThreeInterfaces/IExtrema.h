/*
 ===============================================================
 Interface Extrema
 ===============================================================
*/
#ifndef IExtrema_H
#define IExtrema_H

class IExtrema {
public:
	virtual double getMinimum() const =0;
	virtual double getMaximum() const =0;
};

#endif
