class Superclass
{
public:
	// Fix 1. Note that since we are now declaring the copy constructor, we now need to provide our own default constructor.
	Superclass(){}


	// Fix 2. If a copy constructor is needed to stay public, then an alternative is to create at least one pure virtual function.
	//virtual void dontSliceMe() = 0;
private:
	// Fix 1. Prohibited: We will not define this method.
	//Superclass(const Superclass& other);
};

class Subclass : public Superclass
{
	int val;

	// Fix 2.
	//virtual void dontSliceMe();
};



int main()
{
	Subclass sub;
	
	// This causes slicing. The field 'val' from Subclass is not coped as part of the assignment!
	// Fix 1 makes this more apparent by triggering a compilation error.
	// Fix 2 does as well.
	Superclass super = sub; 

	// However, you can still do the following with any of the fixes, or none:
	Superclass* superDuper = &sub;
}