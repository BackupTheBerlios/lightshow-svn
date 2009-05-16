
public:
	wxString* gp_stor_name() { return &p_stor_name; };
	simap* gp_id_map() { return &p_id_map; };
	ibmap* gp_dont_show_map() { return &p_dont_show_map; };
	ibmap* gp_editable_map() { return &p_editable_map; };
	ibmap* gp_dont_save_map() { return &p_dont_save_map; };
	iimap* gp_column_width() { return &p_column_width; };

private:
	static wxString p_stor_name;
	static simap p_id_map;
	static ibmap p_dont_show_map;
	static ibmap p_editable_map;
	static ibmap p_dont_save_map;
	static iimap p_column_width;


#define DECLARE_STATIC_STC(classname)	wxString classname::p_stor_name;	\
										simap classname::p_id_map;			\
										ibmap classname::p_dont_show_map;	\
										ibmap classname::p_editable_map;	\
										ibmap classname::p_dont_save_map;	\
										iimap classname::p_column_width;
										