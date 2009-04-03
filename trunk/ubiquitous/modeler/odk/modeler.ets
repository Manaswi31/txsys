File format:	editor configuration

# Program-wide information
program_banner:     "OPNET Modeler %V"
copyright:			"Copyright (c) 1986-2009 OPNET Technologies, Inc."
icon_dbs:			opnet_core_actions, opnet_core_objects, sys, flm, ace, sce, mce, design, l2f
program_resources:	netdoc
required_mod_dirs: models
ets_initialization: ace_decoder, ma_dbox, nt_traf_ctr_default_plugins

#menus to be brought up at startup
start_editor
	name:			System	
	base_type:		System
	title:			"System"
	operation_list_files:	std_shortcut_operations,std_help_operations,std_system_operations
end_editor

# License management editor
start_editor
	name:			licenseman
	base_type:		licenseman
	title:			"License Manager"
	operation_list_files:	std_shortcut_operations,std_help_operations,std_license_operations
end_editor

# Project Editor
start_editor
	name:			project
	base_type:		project
	title:			"Project"
	group:			project
	#icon:			"project_editor"
	operation_list_files:	std_header_operations
	operation_list_files:	std_project_file_operations
	operation_list_files:	std_project_edit_operations
	operation_list_files:	std_project_view_operations
	operation_list_files:	std_project_scenarios_operations
	operation_list_files:	std_project_topology_operations
	operation_list_files:	std_project_traffic_operations
	operation_list_files:	std_project_services_operations
	operation_list_files: 	std_project_design_operations
	operation_list_files:	std_project_des_operations
	operation_list_files:	std_project_3dnv_operations
	operation_list_files:	std_help_operations
	operation_list_files:	std_shortcut_operations
	operation_list_files:	std_project_icon_operations
	operation_list_files:	ctcommsim_operations
	#operation_list_files:   ctcommsim_menu	
end_editor

# wjb
# CTCommSim Menu

# Network Whiteboard
start_editor
	name:			whiteboard
	base_type:		whiteboard
	title:			"Network Whiteboard"
	group:			project
	operation_list_files:	std_wb_operations,std_shortcut_operations,std_header_operations,std_help_operations
end_editor

# NetMapper Diagram
start_editor
	name:			netmapper_diagram
	base_type:		netmapper_diagram
	title:			"NetMapper Diagram"
	group:			project
	product options:	netmapper_editor
	operation_list_files:	std_wb_operations,std_shortcut_operations,std_header_operations,std_help_operations
end_editor

# NetMapper Template
start_editor
	name:			netmapper_template
	base_type:		netmapper_template
	title:			"NetMapper Template"
	group:			project
	product options:	netmapper_editor
	operation_list_files:	std_wb_operations,std_shortcut_operations,std_header_operations,std_help_operations
end_editor

# Dialog Box Resource Editor
start_editor
	name:			wrc
	base_type:		wrc
	title:			"Dialog Box Resource File"
	icon:			"wrc_editor"
	group:			primary
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_resource_operations
	product options: odk
	product options: odktools
end_editor	

# ETS Configuration Editor
start_editor
	name:			etsconfig
	base_type:		etsconfig
	title:			"ETS Configuration File"
	icon:			"external_source"
	group:			primary
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_etsconfig_operations
	product options: odk
	product options: odktools
end_editor	


# Application Characterization Editor
start_editor
	name:			ace
	base_type:		ace
	product options: ace
	title:			"ACE"
	icon:			"ace_tool"
	group:			ace
	operation_list_files:	std_shortcut_operations,std_header_operations,std_ace_help_operations,std_ace_operations
end_editor

# ACE QuickView
start_editor
	name:			QuickView
	base_type:		QuickView
	product options: adm
	title:			"ACE QuickView"
	icon:			"ace_tool"
	group:			ace
	operation_list_files:	std_ace_qv_operations,std_shortcut_operations,std_header_operations,std_ace_help_operations
end_editor


# Application Editor
start_editor
	name:			ae
	base_type:		ae
	product options: modeler
	title:			"ACE Whiteboard"
	icon:			"ace_tool"
	group:			ace
	operation_list_files:	std_ae_operations,std_shortcut_operations,std_header_operations,std_ace_help_operations
end_editor

# Server Characterization Editor
start_editor
	name:			sce
	base_type:		sce
	product options: sce
	title:			"Server Characterization"
	#icon:			"sce_tool"
	operation_list_files:	std_shortcut_operations
	operation_list_files:	std_header_operations
	operation_list_files:	std_help_operations
	operation_list_files:	std_sce_operations
	operation_list_files:	std_sce_icon_operations
end_editor

# Mainframe Characterization Editor
start_editor
	name:			mce
	base_type:		mce
	product options: mce
	title:			"Mainframe Characterization"
	#icon:			"mce_tool"
	operation_list_files:	std_shortcut_operations
	operation_list_files:	std_header_operations
	operation_list_files:	std_help_operations
	operation_list_files:	std_mce_operations
	operation_list_files:	std_mce_icon_operations
end_editor

# Node Editor
start_editor
	name:			node
	base_type:		node
	title:			"Node Model"
	icon:			"node_editor"
	group:			process
	operation_list_files:	std_shortcut_operations,std_header_operations,std_edit_operations,std_help_operations,std_node_operations
end_editor

# Process Editor
start_editor
	name:			process
	base_type:		process
	title:			"Process Model"
	icon:			"process_editor"
	group:			process
	operation_list_files:	std_shortcut_operations,std_header_operations,std_edit_operations,std_help_operations,std_process_help_operations,std_process_operations
end_editor

# Link Editor
start_editor
	name:			link
	base_type:		link
	title:			"Link Model"
	group:			process
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_link_operations
end_editor

# Path Model Editor
start_editor
	name:			path
	base_type:		path
	title:			"Path Model"
	group:			process
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_path_operations
end_editor

# Demand Model Editor
start_editor
	name:			demand
	base_type:		demand
	title:			"Demand Model"
	group:			process
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_demand_operations
end_editor

# ETS Source Editor
start_editor
	name:			etssrc
	base_type:		etssrc
	title:			"ETS Source (C code)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_etssrc_operations
end_editor	

# ETS Source Editor (C++)
start_editor
	name:			etssrc_cpp
	base_type:		etssrc_cpp
	title:			"ETS Source (C++ code)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_etssrc_operations
end_editor	

# ETS Source Editor (Python)
start_editor
	name:			etssrc_python
	base_type:		etssrc_python
	title:			"ETS Source (Python code)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_etssrc_python_operations
end_editor	

# External Source Editor
start_editor
	name:			extsrc
	base_type:		extsrc
	title:			"External Source (C code)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_extsrc_operations
end_editor	

# External Source Editor (C++)
start_editor
	name:			extsrc_cpp
	base_type:		extsrc_cpp
	title:			"External Source (C++ code)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_extsrc_operations
end_editor	

# Header file
start_editor
	name:			header
	base_type:		header
	title:			"Header file (C/C++, .h)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations
end_editor	

# Header file
start_editor
	name:			header_cpp
	base_type:		header_cpp
	title:			"Header file (C++, .hpp)"
	icon:			"external_source"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations
end_editor	

# Pipeline Stage Editor (C)
start_editor
	name:			plstage
	base_type:		plstage
	title:			"Pipeline Stage (C code)"
	icon:			"pipeline_stage"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_plstage_operations
end_editor	

# Pipeline Stage Editor (C++)
start_editor
	name:			plstage_cpp
	base_type:		plstage_cpp
	title:			"Pipeline Stage (C++ code)"
	icon:			"pipeline_stage"
	group:			source
	file_chooser:	browse
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_process_help_operations,std_plstage_operations
end_editor	

# Network Editor
start_editor
	name:			network
	base_type:		network
	title:			"Network Model"
	#icon:			"network_editor"
	group:			scenario
	operation_list_files:	std_header_operations
	operation_list_files:	std_network_file_operations
	operation_list_files:	std_network_edit_operations
	operation_list_files:	std_network_view_operations
	operation_list_files:	std_network_network_operations
	operation_list_files:	std_network_terrain_operations
	operation_list_files:	std_help_operations
	operation_list_files:	std_shortcut_operations
	operation_list_files:	std_network_icon_operations
end_editor

# Probe Editor
start_editor
	name:			probe
	base_type:		probe
	title:			"Probe Model"
	icon:			"probe_tool"
	group:			scenario
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_probe_operations,std_modeler_probe_operations
end_editor

# Simulation Tool
start_editor
	name:			simulation
	base_type:		simulation
	title:			"Simulation Sequence"
	icon:			"simulation_tool"
	group:			scenario
	operation_list_files:	std_shortcut_operations,std_header_operations,std_edit_operations,std_help_operations,std_simulation_operations,std_modeler_simulation_operations
end_editor

# Antenna Editor
start_editor
	name:			antenna
	base_type:		antenna
	product options: wireless
	title:			"Antenna Pattern"
	icon:			"parameter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_antenna_operations
end_editor

# External System Editor
start_editor
	name:			esd
	base_type:		esd
	title:			"External System Definition"
	icon:			"parameter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_esd_operations
end_editor

# Filter Tool
start_editor
	name:			filter
	base_type:		filter
	title:			"Filter Model"
	icon:			"filter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_edit_operations,std_help_operations,std_filter_operations
end_editor

# Environment Files
start_editor
	name:			ef
	base_type:		ef
	title:			"Environment File"
	icon:			"ef_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_ef_operations
end_editor	

# Generic Data Files
start_editor
	name:			gdf
	base_type:		gdf
	title:			"Generic Data File"
	icon:			"gdf_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_gdf_operations
end_editor	

# ICI Editor
start_editor
	name:			ici
	base_type:		ici
	title:			"ICI Format"
	icon:			"parameter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_ici_operations
end_editor

# Icon Editor
start_editor
	name:			icon
	base_type:		icon
	title:			"Icon Database"
	icon:			"icon_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_icon_operations
end_editor

# Modulation Editor
start_editor
	name:			modulation
	base_type:		modulation
	product options: wireless
	title:			"Modulation Curve"
	icon:			"parameter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_modulation_operations
end_editor

# Packet Format Editor
start_editor
	name:			packet
	base_type:		packet
	title:			"Packet Format"
	icon:			"packet_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_edit_operations,std_help_operations,std_packet_operations
end_editor

# PDF Editor
start_editor
	name:			pdf
	base_type:		pdf
	title:			"PDF Model"
	icon:			"parameter_editor"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_pdf_operations
end_editor

# Profile Library Editor
start_editor
	name:			ppl
	base_type:		ppl
	title:			"Profile Library"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_profile_operations
end_editor

# Wireless Domain Model Editor
start_editor
	name:			wdomain
	base_type:		wdomain
	product options: 	wireless
	title:			"Wireless Domain Model"
	group:			misc
	operation_list_files:	std_shortcut_operations,std_header_operations,std_help_operations,std_parameter_operations,std_wdomain_operations
end_editor





