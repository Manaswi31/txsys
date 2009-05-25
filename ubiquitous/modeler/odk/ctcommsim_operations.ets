# Standard button list for all editors
#
# IMPORTANT: Changes to this file should also be made to other
# related .ets files (std_*_help_operations.ets)
#
File format:	operation list

start_operation
	#title: "æˆ˜æœ¯é€šä¿¡ä»¿çœŸ"
	title: "CTCommSim"
	position:	0R
end_operation

start_operation 
	operation:		exec_function wireless_deployment_wizard wireless_deployment_wizard_launch
	product options:	wireless
	menu string:		"Deploy Wireless Network..."
	menu header: "CTCommSim"
	#menu header:	"æˆ˜æœ¯é€šä¿¡ä»¿çœŸ"
	guidance string:	"launch the Wireless Network Deployment Wizard"
	position:			1
end_operation

start_operation
	operation:	exec_builtin view_doc
	menu string:	"ÅäÖÃÍøÂç"
	#menu string:	"Product Documentation"
	menu header:	"CTCommSim"
	position:	2
end_operation

start_operation
	operation:	exec_builtin view_doc
	menu string:	"Product Documentation"
	menu header:	"CTCommSim"
	shortcut:	"F1"
	position:	30
end_operation

