/*
 ===============================================================
 Interface IValue
 ===============================================================
*/
#ifndef IValue_H
#define IValue_H

class IValue {
public:
	virtual void setValue(double v) =0;
	virtual double getValue() const =0;
	virtual double getHistoricValue(int n) const =0;
	virtual int historySize() const =0;
	virtual void clearHistory() =0;
};

#endif
