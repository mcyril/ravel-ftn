typedef struct {	const char	*state_name;	ProcPtr		state_func;} STATES, *STATEP;short state_machine (STATEP, void *, short );