# Serialize

# using it like this

	bool b = true;
	int i32 = 2;
	double f64 = 3.0;
	std::string strMsg = "this is a test str.";

	CSerialize sz;
	sz << b << i32 << f64 << strMsg;

	std::cout << sz.GetSerStatus() << sz.GetIndex() << sz.Serialize() << std::endl;

# ---------------------------------------------
	CSerialize rsz(sz.Serialize(), sz.GetIndex());
	bool b_2;
	int i32_2;
	double f64_2;

	std::string strMsg_2;
	rsz >> b_2 >> i32_2 >> f64_2 >> strMsg_2;

	std::cout << b_2 << "|" << i32_2  << "|"  << f64_2 << "|"  << strMsg_2 << std::endl;

	sz.Release(); //optional
	//rsz.Release();
