var
	player_max_exp			: [psect(player_data)]
					  integer;	{ Max exp possible    }
	seed				: [psect(player_data),global]
					  unsigned;	{ Contains seed #     }
	randes_seed			: [psect(setup_data)]
					  unsigned;	{ For encoding colors }
	town_seed			: [psect(generate_data)]
					  unsigned;	{ Seed for town genera}
	channel				: [psect(io_data),global]
					  integer;	{ I/O channel #       }
	io_bin_pause			: [psect(io_data)]
					  quad_type;	{ I/O pause time      }
	cur_height,cur_width		: [psect(player_data)]
					  integer;	{ Cur dungeon size    }
	dun_level			: [psect(player_data)]
					  integer;	{ Cur dungeon level   }
	missle_ctr			: [psect(player_data)]
					  integer;	{ Counter for missles }
	msg_line			: [psect(player_data)]
					  integer;	{ Contains message txt}
	msg_flag			: [psect(player_data)]
					  boolean;	{ Set with first msg  }
	old_msg				: [psect(player_data)]
					  vtype;	{ Last message	      }
	generate			: [psect(setup_data)]
					  boolean;	{ Generate next level }
	death				: [psect(player_data)]
					  boolean;	{ True if died	      }
	died_from			: [psect(player_data)]
					  vtype;	{ What killed him     }
	find_flag			: [psect(player_data)]
					  boolean;	{ Used in MORIA	      }
	reset_flag			: [psect(player_data)]
					  boolean;	{ Used in MORIA	      }
	cave_flag			: [psect(player_data)]
					  boolean;	{ Used in GET_PANEL   }
	light_flag			: [psect(player_data)]
					  boolean;	{ Used in MOVE_LIGHT  }
	redraw				: [psect(player_data)]
					  boolean;	{ For redraw screen   }
	stat_column			: [psect(player_data)]
					  integer;	{ Column for stats    }
	print_stat			: [psect(player_data)]
					  unsigned;	{ Flag for stats      }
	turn				: [psect(player_data)]
					  integer;	{ Cur trun of game    }
	wizard1				: [psect(player_data)]
					  boolean;	{ Wizard flag	      }
	wizard2				: [psect(player_data)]
					  boolean;	{ Wizard flag	      }
	used_line			: [psect(player_data)]
					  array [2..23] of boolean;
	password1			: [psect(setup_data)]
					  packed array [1..12] of char;
	password2			: [psect(setup_data)]
					  packed array [1..12] of char;
	wdata				: [psect(setup_data)]
					  array [1..2,0..12] of unsigned;
	days				: [psect(setup_data)]
					  array [1..7] of vtype;
	closing_flag			: [psect(player_data)]
					  integer;	{ Used for closing   }

	{ Bit testing array						}
	bit_array			: [psect(player_data)]
					  array [1..32] of unsigned;

	{ External file names; are all located in directory with image	}
	MORIA_HOU			: vtype;
	MORIA_MOR			: vtype;
	MORIA_MAS			: vtype;
	MORIA_TOP			: vtype;
	MORIA_HLP			: vtype;

	{  Following are calculated from max dungeon sizes		}
	max_panel_rows,max_panel_cols	: integer;
	quart_height,quart_width	: integer;
	panel_row,panel_col		: integer;
	panel_row_min,panel_row_max	: integer;
	panel_col_min,panel_col_max	: integer;
	panel_col_prt,panel_row_prt	: integer;

	{  Following are all floor definitions				}
	cave				: [psect(moria_data)]
					  array [1..max_height] of row_floor;
	blank_floor			: cave_type;
	dopen_floor			: floor_type;
	lopen_floor			: floor_type;
	corr_floor1			: floor_type;
	corr_floor2			: floor_type;
	corr_floor3			: floor_type;
	corr_floor4			: floor_type;
	rock_wall1			: floor_type;
	rock_wall2			: floor_type;
	rock_wall3			: floor_type;
	boundry_wall			: floor_type;

	{  Following are set definitions				}
	floor_set			: obj_set;
	wall_set			: obj_set;
	pwall_set			: obj_set;
	corr_set			: obj_set;
	trap_set			: obj_set;
	light_set			: obj_set;

	{ Following are player variables				}
	py			: player_type;
	player_title		: [psect(player_data)]
				  array [1..max_class] of
				  array [1..max_player_level] of btype;
	player_exp		: [psect(player_data)]
				  array [1..max_player_level] of integer;
	acc_exp			: [psect(player_data)]
				  real;	{ Accumulator for fractional exp}
	bare_hands		: [psect(player_data)]
				  dtype;
	char_row		: integer;
	char_col		: integer;
	com_val			: integer;
	pclass			: integer;
	sex_type		: vtype;
	race			: [psect(create_data)]
				  array [1..max_races] of race_type;
	background		: [psect(create_data)]
				  array [1..max_background] of background_type;
	rgold_adj		: [psect(store_data)]
				  array [1..max_races] of
				  array [1..max_races] of real;
	class			: [psect(create_data)]
				  array [1..max_class] of class_type;
	magic_spell		: [psect(player_data)]
				  array [1..max_class] of 
				  array [1..31] of spell_type;
	mush			: treasure_type;
	player_init		: [psect(create_data)]
				  array [1..max_class] of
				  array [1..5] of byteint;
	total_winner		: boolean;

	{ Following are store definitions				}
	owners			: [psect(store_data)]
				  array [1..max_owners] of owner_type;
	store			: [psect(store_data)]
				  array [1..max_stores] of store_type;
	store_door		: [psect(generate_data)]
				  array [1..max_stores] of treasure_type;
	store_choice		: [psect(store_data)]
				  array [1..max_stores] of 
				  array [1..store_choices] of integer;
	store_buy		: [psect(store_data)]
				  array [1..max_stores] of obj_set;

	{ Following are treasure arrays	and variables			}
	object_list		: 
				  array [1..max_objects] of treasure_type;
	object_ident		: 
				  array [1..max_objects] of boolean;
	t_level			: 
				  array [0..max_obj_level] of integer;
	gold_list		: 
				  array [1..max_gold]    of treasure_type;
	t_list			: 
				  array [1..max_talloc]  of treasure_type;
	inventory		: 
				  array [1..inven_max]	 of treasure_type;
	inventory_init		: 
				  array [1..inven_init_max] of treasure_type;
	blank_treasure		: treasure_type;
	inven_ctr		: [psect(player_data)]
				  integer;	{ Total different obj's	}
	inven_weight		: [psect(player_data)]
				  integer;	{ Cur carried weight	}
	equip_ctr		: [psect(player_data)]
				  integer;	{ Cur equipment ctr	}
	tcptr			: [psect(moria_data)]
				  integer;	{ Cur treasure heap ptr	}

	{ Following are feature objects defined for dungeon		}
	trap_lista		: [psect(generate_data)]
				  array [1..max_trapa]   of treasure_type;
	trap_listb		: [psect(generate_data)]
				  array [1..max_trapb]   of treasure_type;
	scare_monster		: [psect(generate_data)]
				  treasure_type;	{ Special trap	}
	rubble			: [psect(generate_data)]
				  treasure_type;
	door_list		: [psect(generate_data)]
				  array [1..3]		 of treasure_type;
	up_stair		: [psect(generate_data)]
				  treasure_type;
	down_stair		: [psect(generate_data)]
				  treasure_type;

	{ Following are creature arrays and variables			}
	c_list		: [psect(moria_data)]
			  array [1..max_creatures] of creature_type;
	m_list		: [psect(moria_data)]
			  array [1..max_malloc]    of monster_type;
	m_level		: [psect(generate_data)]
			  array [0..max_mons_level] of integer;
	blank_monster	: [psect(generate_data)]
			  monster_type;	{ Blank monster values	}
	muptr		: [psect(generate_data)]
			  integer;	{ Cur used monster ptr	}
	mfptr		: [psect(generate_data)]
			  integer;	{ Cur free monster ptr	}
	mon_tot_mult	: [psect(moria_data)]
			  integer;	{ # of repro's of creature	}

	{ Following are arrays for descriptive pieces			}
	colors			: [psect(setup_data)]
				  array [1..max_colors]	 of atype;
	mushrooms		: [psect(setup_data)]
				  array [1..max_mush]    of atype;
	woods			: [psect(setup_data)]
				  array [1..max_woods]   of atype;
	metals			: [psect(setup_data)]
				  array [1..max_metals]  of atype;
	rocks			: [psect(setup_data)]
				  array [1..max_rocks]   of atype;
	amulets			: [psect(setup_data)]
				  array [1..max_amulets] of atype;
	syllables		: [psect(setup_data)]
				  array [1..max_syllables] of dtype;
	vowel_set		: [psect(moria_data)]
				  char_set;

	{ Following are variables for the Save Character Routines	}
	finam			: [psect(save_data)]
				  vtype;
	key_rec			: [psect(save_data)]
				  key_type;

	{ Cursor variables, used for cursor positioning			}
	cursor_r	: [psect(io_data),global]
			  array [1..24] of string[10];
	curlen_r	: integer;
	cursor_c	: [psect(io_data),global]
			  array [1..80] of string[10];
	curlen_c	: integer;
	cursor_l	: integer;
	row_first	: boolean;
	cursor_erl	: string[10];
	cursor_erp	: string[10];
