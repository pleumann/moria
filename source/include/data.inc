var

	player_max_exp			: 
					  integer;	{ Max exp possible    }
	seed				: 
					  unsigned;	{ Contains seed #     }
	randes_seed			: 
					  unsigned;	{ For encoding colors }
	town_seed			: 
					  unsigned;	{ Seed for town genera}
	channel				: 
					  integer;	{ I/O channel #       }
	io_bin_pause			: 
					  quad_type;	{ I/O pause time      }
	cur_height,cur_width		: 
					  integer;	{ Cur dungeon size    }
	dun_level			: 
					  integer;	{ Cur dungeon level   }
	msg_line			: 
					  integer;	{ Contains message txt}
	msg_flag			: 
					  boolean;	{ Set with first msg  }
	old_msg				: 
					  vtype;	{ Last message	      }
	generate			: 
					  boolean;	{ Generate next level }
	died_from			: 
					  vtype;	{ What killed him     }
	find_flag			: 
					  boolean;	{ Used in MORIA	      }
	reset_flag			: 
					  boolean;	{ Used in MORIA	      }
	cave_flag			: 
					  boolean;	{ Used in GET_PANEL   }
	light_flag			: 
					  boolean;	{ Used in MOVE_LIGHT  }
	redraw				: 
					  boolean;	{ For redraw screen   }
	password1			: 
					  packed array [1..12] of char;
	password2			: 
					  packed array [1..12] of char;

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
	cave				: 
					  array [1..max_height] of row_floor;
	com_val			: integer;
	store			: 
				  array [1..max_stores] of store_type;
	t_level			: 
				  array [0..max_obj_level] of integer;
	t_list			: 
				  array [1..max_talloc]  of treasure_type;
	inventory		: 
				  array [1..inven_max]	 of treasure_type;
	tcptr			: 
				  integer;	{ Cur treasure heap ptr	}
	m_list		: 
			  array [1..max_malloc]    of monster_type;
	m_level		: 
			  array [0..max_mons_level] of integer;
	muptr		: 
			  integer;	{ Cur used monster ptr	}
	mfptr		: 
			  integer;	{ Cur free monster ptr	}
	mon_tot_mult	: 
			  integer;	{ # of repro's of creature	}

	{ Following are variables for the Save Character Routines	}
	finam			: 
				  vtype;
	key_rec			: 
				  key_type;

	{ Cursor variables, used for cursor positioning			}
	cursor_r	: 
			  array [1..24] of string[10];
	curlen_r	: integer;
	cursor_c	: 
			  array [1..80] of string[10];
	curlen_c	: integer;
	cursor_l	: integer;
	row_first	: boolean;
	cursor_erl	: string[10];
	cursor_erp	: string[10];

const


	wizard1 	:  
					  boolean =  false;
	wizard2         :  
					  boolean =  false;
	{ God and Wizard passwords: God is for debugging purposes only. }
	wdata           :  
					  array [1..2,0..12] of unsigned = (
		(011065,87,36,139,197,12,22,228,250,54,148,136,163),
		(122565,181,170,214,182,212,8,195,173,86,76,252,124)
			  );
	used_line       :  
					  array [2..23] of boolean =  (22 of false);
	death           :  
					  boolean =  false;
	total_winner    :  boolean =  false;
	stat_column     :  
					  integer =  1;
	turn            :  
					  integer =  0;
	pclass          :  integer =  0;
	print_stat      :  
					  unsigned =  0;

	{ For the testing of bits				-RAK-	}
	bit_array       :  
					  array [1..32] of unsigned =  (
		$00000001,   { Bit number 1  }
		$00000002,   { Bit number 2  }
		$00000004,   { Bit number 3  }
		$00000008,   { Bit number 4  }
		$00000010,   { Bit number 5  }
		$00000020,   { Bit number 6  }
		$00000040,   { Bit number 7  }
		$00000080,   { Bit number 8  }
		$00000100,   { Bit number 9  }
		$00000200,   { Bit number 10 }
		$00000400,   { Bit number 11 }
		$00000800,   { Bit number 12 }
		$00001000,   { Bit number 13 }
		$00002000,   { Bit number 14 }
		$00004000,   { Bit number 15 }
		$00008000,   { Bit number 16 }
		$00010000,   { Bit number 17 }
		$00020000,   { Bit number 18 }
		$00040000,   { Bit number 19 }
		$00080000,   { Bit number 20 }
		$00100000,   { Bit number 21 }
		$00200000,   { Bit number 22 }
		$00400000,   { Bit number 23 }
		$00800000,   { Bit number 24 }
		$01000000,   { Bit number 25 }
		$02000000,   { Bit number 26 }
		$04000000,   { Bit number 27 }
		$08000000,   { Bit number 28 }
		$10000000,   { Bit number 29 }
		$20000000,   { Bit number 30 }
		$40000000,   { Bit number 31 }
		$80000000    { Bit number 32 }
			);

	{ Operating hours for Moria				-RAK-	}
	{       X = Open; . = Closed                                    }
	days    :  
					  array [1..7] of vtype = (
		'SUN:XXXXXXXXXXXXXXXXXXXXXXXX|',
		'MON:XXXXXXXX.........XXXXXXX|',
		'TUE:XXXXXXXX.........XXXXXXX|',
		'WED:XXXXXXXX.........XXXXXXX|',
		'THU:XXXXXXXX.........XXXXXXX|',
		'FRI:XXXXXXXX.........XXXXXXX|',
		'SAT:XXXXXXXXXXXXXXXXXXXXXXXX|'
		   );

	closing_flag :  
					  integer =  0;

	{ Values for floor types					}
	blank_floor:  cave_type =  (cptr: 0;tptr: 0;fval: 0;fopen: false;fm: false;pl: false;tl: false);
	dopen_floor     :  floor_type =  (  ftval: 1;ftopen: true ); { Dark open floor       }
	lopen_floor     :  floor_type =  (  ftval: 2;ftopen: true ); { Light open floor      }
	corr_floor1     :  floor_type =  (  ftval: 4;ftopen: true ); { Corridor open floor   }
	corr_floor2     :  floor_type =  (  ftval: 5;ftopen: true ); { Room junction marker  }
	corr_floor3     :  floor_type =  (  ftval: 6;ftopen: true ); { Door type floor       }
	corr_floor4     :  floor_type =  (  ftval: 7;ftopen: false); { Secret door type floor}
	{ Floor values 8 and 9 are used in generate             }
	rock_wall1      :  floor_type =  ( ftval: 10;ftopen: false); { Granite rock wall     }
	rock_wall2      :  floor_type =  ( ftval: 11;ftopen: false); { Magma rock wall       }
	rock_wall3      :  floor_type =  ( ftval: 12;ftopen: false); { Quartz rock wall      }
	boundry_wall    :  floor_type =  ( ftval: 15;ftopen: false); { Indestructable wall   }

	{ Player record is special					}
	py              :  player_type =       (
	misc: (name: ' ';race: ' ';sex: ' ';title: ' ';tclass: ' ';
	 max_exp: 0;exp: 0;au: 0;age: 0;ht: 0;wt: 0;lev: 0;max_lev: 0;srh: 0;fos: 0;bth: 0;bthb: 0;mana: 0;
	   mhp: 0;ptohit: 0;ptodam: 0;pac: 0;ptoac: 0;dis_th: 0;dis_td: 0;dis_ac: 0;dis_tac: 0;disarm: 0;
	   save: 0;sc: 0;pclass: 0;prace: 0;hitdie: 0;stl: 0;expfact: 0;cmana: 0;chp: 0;
	 history: ('','','','',''));
	stat: (str: 0;cstr: 0;dex: 0;cdex: 0;con: 0;ccon: 0;int: 0;cint: 0;wis: 0;cwis: 0;chr: 0;cchr: 0);
	flags: (status: 0;rest: 0;blind: 0;paralysis: 0;confused: 0;food: 7500;food_digested: 2;
	  protection: 0;speed: 0;fast: 0;slow: 0;afraid: 0;poisoned: 0;image: 0;protevil: 0;invuln: 0;
	  hero: 0;shero: 0;blessed: 0;resist_heat: 0;resist_cold: 0;detect_inv: 0;word_recall: 0;
	  see_infra: 0;tim_infra: 0;
	 see_inv: false;teleport: false;free_act: false;slow_digest: false;aggravate: false;fire_resist:
	   false;cold_resist: false;acid_resist: false;regenerate: false;
	 lght_resist: false;ffall: false;sustain_str: false;sustain_int: false;sustain_wis: false;
	   sustain_con: false;sustain_dex: false;sustain_chr: false;confuse_monster: false)
				);

	bare_hands	:  
				  dtype =  '1d1';

	acc_exp 	:  
				  real =  0.0;

	{ Each character class has a list of spells they can use.  In	}
	{ cases the entire array is blank                               }

	magic_spell	:  
				  array [1..max_class] of 
				  array [1..31] of spell_type = 	(	(		{ Warrior	}
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false)
					),
					(               { Mage          }
 (sname: 'Magic Missile'               ; slevel: 1; smana: 1;  sexp: 5; sfail: 22;learned: false),
 (sname: 'Detect Monsters'             ; slevel: 1; smana: 1;  sexp: 5; sfail: 23;learned: false),
 (sname: 'Phase Door'                  ; slevel: 1; smana: 2;  sexp: 4; sfail: 24;learned: false),
 (sname: 'Light Area'                  ; slevel: 1; smana: 2;  sexp: 4; sfail: 26;learned: false),
 (sname: 'Cure Light Wounds'           ; slevel: 3; smana: 3;  sexp: 8; sfail: 25;learned: false),
 (sname: 'Find Hidden Traps/Doors'     ; slevel: 3; smana: 3;  sexp: 6; sfail: 55;learned: false),
 (sname: 'Stinking Cloud'              ; slevel: 3; smana: 4;  sexp: 8; sfail: 27;learned: false),
 (sname: 'Confusion'                   ; slevel: 3; smana: 4;  sexp: 6; sfail: 30;learned: false),
 (sname: 'Lightning Bolt'              ; slevel: 5; smana: 4; sexp: 25; sfail: 30;learned: false),
 (sname: 'Trap/Door Destruction'       ; slevel: 5; smana: 5; sexp: 30; sfail: 30;learned: false),
 (sname: 'Sleep I'                     ; slevel: 5; smana: 5; sexp: 20; sfail: 30;learned: false),
 (sname: 'Cure Poison'                 ; slevel: 5; smana: 5; sexp: 25; sfail: 35;learned: false),
 (sname: 'Teleport Self'               ; slevel: 7; smana: 6; sexp: 35; sfail: 35;learned: false),
 (sname: 'Remove Curse'                ; slevel: 7; smana: 6; sexp: 40; sfail: 50;learned: false),
 (sname: 'Frost Bolt'                  ; slevel: 7; smana: 6; sexp: 50; sfail: 40;learned: false),
 (sname: 'Turn Stone to Mud'           ; slevel: 9; smana: 7; sexp: 75; sfail: 44;learned: false),
 (sname: 'Create Food'                 ; slevel: 9; smana: 7; sexp: 75; sfail: 45;learned: false),
 (sname: 'Recharge Item I'             ; slevel: 9; smana: 7; sexp: 90; sfail: 75;learned: false),
 (sname: 'Sleep II'                    ; slevel: 9; smana: 7; sexp: 75; sfail: 45;learned: false),
 (sname: 'Polymorph Other'             ;slevel: 11; smana: 7;sexp: 100; sfail: 45;learned: false),
 (sname: 'Identify'                    ;slevel: 11; smana: 7; sexp: 75; sfail: 99;learned: false),
 (sname: 'Sleep III'                   ;slevel: 13; smana: 7; sexp: 90; sfail: 50;learned: false),
 (sname: 'Fire Bolt'                   ;slevel: 15; smana: 9;sexp: 100; sfail: 50;learned: false),
 (sname: 'Slow Monster'                ;slevel: 17; smana: 9;sexp: 125; sfail: 50;learned: false),
 (sname: 'Frost Ball'                  ;slevel: 19;smana: 12;sexp: 150; sfail: 55;learned: false),
 (sname: 'Recharge Item II'            ;slevel: 21;smana: 12;sexp: 175; sfail: 90;learned: false),
 (sname: 'Teleport Other'              ;slevel: 23;smana: 12;sexp: 200; sfail: 60;learned: false),
 (sname: 'Haste Self'                  ;slevel: 25;smana: 12;sexp: 250; sfail: 65;learned: false),
 (sname: 'Fire Ball'                   ;slevel: 29;smana: 18;sexp: 350; sfail: 65;learned: false),
 (sname: 'Word of Destruction'         ;slevel: 33;smana: 21;sexp: 500; sfail: 80;learned: false),
 (sname: 'Genocide'                    ;slevel: 37;smana: 25;sexp: 800; sfail: 95;learned: false)
					),
					(               { Priest        }
 (sname: 'Detect Evil'                 ; slevel: 1; smana: 1;  sexp: 3; sfail: 10;learned: false),
 (sname: 'Cure Light Wounds'           ; slevel: 1; smana: 2;  sexp: 4; sfail: 15;learned: false),
 (sname: 'Bless'                       ; slevel: 1; smana: 2;  sexp: 3; sfail: 20;learned: false),
 (sname: 'Remove Fear'                 ; slevel: 1; smana: 2;  sexp: 3; sfail: 25;learned: false),
 (sname: 'Call Light'                  ; slevel: 3; smana: 2;  sexp: 6; sfail: 25;learned: false),
 (sname: 'Find Traps'                  ; slevel: 3; smana: 3;  sexp: 8; sfail: 27;learned: false),
 (sname: 'Detect Doors/Stairs'         ; slevel: 3; smana: 3;  sexp: 8; sfail: 27;learned: false),
 (sname: 'Slow Poison'                 ; slevel: 3; smana: 3; sexp: 10; sfail: 28;learned: false),
 (sname: 'Blind Creature'              ; slevel: 5; smana: 4; sexp: 16; sfail: 29;learned: false),
 (sname: 'Portal'                      ; slevel: 5; smana: 4; sexp: 20; sfail: 30;learned: false),
 (sname: 'Cure Medium Wounds'          ; slevel: 5; smana: 4; sexp: 20; sfail: 32;learned: false),
 (sname: 'Chant'                       ; slevel: 5; smana: 5; sexp: 20; sfail: 34;learned: false),
 (sname: 'Sanctuary'                   ; slevel: 7; smana: 5; sexp: 30; sfail: 36;learned: false),
 (sname: 'Create Food'                 ; slevel: 7; smana: 5; sexp: 30; sfail: 38;learned: false),
 (sname: 'Remove Curse'                ; slevel: 7; smana: 6; sexp: 35; sfail: 38;learned: false),
 (sname: 'Resist Heat and Cold'        ; slevel: 7; smana: 7; sexp: 35; sfail: 38;learned: false),
 (sname: 'Neutralize Poison'           ; slevel: 9; smana: 6; sexp: 40; sfail: 38;learned: false),
 (sname: 'Orb of Draining'             ; slevel: 9; smana: 7; sexp: 40; sfail: 38;learned: false),
 (sname: 'Cure Serious Wounds'         ; slevel: 9; smana: 7; sexp: 40; sfail: 40;learned: false),
 (sname: 'Sense Invisible'             ;slevel: 11; smana: 8; sexp: 40; sfail: 42;learned: false),
 (sname: 'Protection from Evil'        ;slevel: 11; smana: 8; sexp: 50; sfail: 42;learned: false),
 (sname: 'Earthquake'                  ;slevel: 11; smana: 9; sexp: 60; sfail: 55;learned: false),
 (sname: 'Sense Surroundings'          ;slevel: 13;smana: 10; sexp: 60; sfail: 45;learned: false),
 (sname: 'Cure Critical Wounds'        ;slevel: 13;smana: 11; sexp: 65; sfail: 45;learned: false),
 (sname: 'Turn Undead'                 ;slevel: 15;smana: 12; sexp: 80; sfail: 50;learned: false),
 (sname: 'Prayer'                      ;slevel: 15;smana: 14; sexp: 90; sfail: 50;learned: false),
 (sname: 'Dispell Undead'              ;slevel: 17;smana: 14;sexp: 125; sfail: 55;learned: false),
 (sname: 'Heal'                        ;slevel: 21;smana: 16;sexp: 150; sfail: 60;learned: false),
 (sname: 'Dispell Evil'                ;slevel: 25;smana: 20;sexp: 300; sfail: 70;learned: false),
 (sname: 'Glyph of Warding'            ;slevel: 33;smana: 24;sexp: 500; sfail: 90;learned: false),
 (sname: 'Holy Word'                   ;slevel: 39;smana: 32;sexp: 800; sfail: 99;learned: false)
					),
					(               { Rogue         }
 (sname: 'Magic Missile'               ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Detect Monsters'             ; slevel: 5; smana: 1;  sexp: 2; sfail: 50;learned: false),
 (sname: 'Phase Door'                  ; slevel: 7; smana: 2;  sexp: 4; sfail: 55;learned: false),
 (sname: 'Light Area'                  ; slevel: 9; smana: 3;  sexp: 6; sfail: 60;learned: false),
 (sname: 'Cure Light Wounds'           ;slevel: 11; smana: 4;  sexp: 8; sfail: 65;learned: false),
 (sname: 'Find Hidden Traps/Doors'     ;slevel: 13; smana: 5; sexp: 10; sfail: 70;learned: false),
 (sname: 'Stinking Cloud'              ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Confusion'                   ;slevel: 15; smana: 6; sexp: 12; sfail: 75;learned: false),
 (sname: 'Lightning Bolt'              ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Trap/Door Destruction'       ;slevel: 17; smana: 7; sexp: 15; sfail: 80;learned: false),
 (sname: 'Sleep I'                     ;slevel: 19; smana: 8; sexp: 20; sfail: 85;learned: false),
 (sname: 'Cure Poison'                 ;slevel: 21; smana: 9; sexp: 25; sfail: 90;learned: false),
 (sname: 'Teleport Self'               ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Remove Curse'                ;slevel: 23;smana: 10; sexp: 30; sfail: 95;learned: false),
 (sname: 'Frost Bolt'                  ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Turn Stone to Mud'           ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Create Food'                 ;slevel: 25;smana: 12; sexp: 35; sfail: 95;learned: false),
 (sname: 'Recharge Item I'             ;slevel: 27;smana: 15; sexp: 45; sfail: 99;learned: false),
 (sname: 'Sleep II'                    ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Polymorph Other'             ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Identify'                    ;slevel: 29;smana: 18; sexp: 75; sfail: 99;learned: false),
 (sname: 'Sleep III'                   ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Fire Bolt'                   ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Slow Monster'                ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Frost Ball'                  ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Recharge Item II'            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Teleport Other'              ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Haste Self'                  ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Fire Ball'                   ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Word of Destruction'         ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false),
 (sname: 'Genocide'                    ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false)
					),
					(               { Ranger        }
 (sname: 'Magic Missile'               ; slevel: 3; smana: 1;  sexp: 6; sfail: 30;learned: false),
 (sname: 'Detect Monsters'             ; slevel: 3; smana: 2;  sexp: 6; sfail: 35;learned: false),
 (sname: 'Phase Door'                  ; slevel: 3; smana: 2;  sexp: 8; sfail: 35;learned: false),
 (sname: 'Light Area'                  ; slevel: 5; smana: 3;  sexp: 8; sfail: 35;learned: false),
 (sname: 'Cure Light Wounds'           ; slevel: 5; smana: 3;  sexp: 8; sfail: 40;learned: false),
 (sname: 'Find Hidden Traps/Doors'     ; slevel: 5; smana: 4; sexp: 10; sfail: 45;learned: false),
 (sname: 'Stinking Cloud'              ; slevel: 7; smana: 6; sexp: 24; sfail: 40;learned: false),
 (sname: 'Confusion'                   ; slevel: 7; smana: 6; sexp: 20; sfail: 40;learned: false),
 (sname: 'Lightning Bolt'              ; slevel: 9; smana: 7; sexp: 30; sfail: 40;learned: false),
 (sname: 'Trap/Door Destruction'       ; slevel: 9; smana: 8; sexp: 30; sfail: 45;learned: false),
 (sname: 'Sleep I'                     ;slevel: 11; smana: 8; sexp: 40; sfail: 40;learned: false),
 (sname: 'Cure Poison'                 ;slevel: 11; smana: 9; sexp: 40; sfail: 45;learned: false),
 (sname: 'Teleport Self'               ;slevel: 13;smana: 10; sexp: 50; sfail: 45;learned: false),
 (sname: 'Remove Curse'                ;slevel: 13;smana: 11; sexp: 50; sfail: 55;learned: false),
 (sname: 'Frost Bolt'                  ;slevel: 15;smana: 12; sexp: 60; sfail: 50;learned: false),
 (sname: 'Turn Stone to Mud'           ;slevel: 15;smana: 13; sexp: 60; sfail: 50;learned: false),
 (sname: 'Create Food'                 ;slevel: 17;smana: 17; sexp: 60; sfail: 55;learned: false),
 (sname: 'Recharge Item I'             ;slevel: 17;smana: 17; sexp: 70; sfail: 90;learned: false),
 (sname: 'Sleep II'                    ;slevel: 21;smana: 17; sexp: 70; sfail: 55;learned: false),
 (sname: 'Polymorph Other'             ;slevel: 21;smana: 19; sexp: 70; sfail: 60;learned: false),
 (sname: 'Identify'                    ;slevel: 23;smana: 25; sexp: 80; sfail: 95;learned: false),
 (sname: 'Sleep III'                   ;slevel: 23;smana: 20; sexp: 80; sfail: 60;learned: false),
 (sname: 'Fire Bolt'                   ;slevel: 25;smana: 20; sexp: 80; sfail: 60;learned: false),
 (sname: 'Slow Monster'                ;slevel: 25;smana: 21; sexp: 80; sfail: 65;learned: false),
 (sname: 'Frost Ball'                  ;slevel: 27;smana: 21; sexp: 90; sfail: 65;learned: false),
 (sname: 'Recharge Item II'            ;slevel: 29;smana: 23; sexp: 90; sfail: 95;learned: false),
 (sname: 'Teleport Other'              ;slevel: 31;smana: 25;sexp: 100; sfail: 70;learned: false),
 (sname: 'Haste Self'                  ;slevel: 33;smana: 25;sexp: 150; sfail: 75;learned: false),
 (sname: 'Fire Ball'                   ;slevel: 35;smana: 25;sexp: 200; sfail: 80;learned: false),
 (sname: 'Word of Destruction'         ;slevel: 37;smana: 30;sexp: 500; sfail: 95;learned: false),
 (sname: ''                            ;slevel: 99;smana: 99;  sexp: 0;  sfail: 0;learned: false)
					),
					(               { Paladin       }
 (sname: 'Detect Evil'                 ; slevel: 1; smana: 1;  sexp: 4; sfail: 30;learned: false),
 (sname: 'Cure Light Wounds'           ; slevel: 2; smana: 2;  sexp: 8; sfail: 35;learned: false),
 (sname: 'Bless'                       ; slevel: 3; smana: 3; sexp: 12; sfail: 35;learned: false),
 (sname: 'Remove Fear'                 ; slevel: 5; smana: 3; sexp: 20; sfail: 35;learned: false),
 (sname: 'Call Light'                  ; slevel: 5; smana: 4; sexp: 20; sfail: 35;learned: false),
 (sname: 'Find Traps'                  ; slevel: 7; smana: 5; sexp: 25; sfail: 40;learned: false),
 (sname: 'Detect Doors/Stairs'         ; slevel: 7; smana: 5; sexp: 25; sfail: 40;learned: false),
 (sname: 'Slow Poison'                 ; slevel: 9; smana: 7; sexp: 30; sfail: 40;learned: false),
 (sname: 'Blind Creature'              ; slevel: 9; smana: 7; sexp: 30; sfail: 40;learned: false),
 (sname: 'Portal'                      ; slevel: 9; smana: 8; sexp: 30; sfail: 40;learned: false),
 (sname: 'Cure Medium Wounds'          ;slevel: 11; smana: 9; sexp: 40; sfail: 40;learned: false),
 (sname: 'Chant'                       ;slevel: 11;smana: 10; sexp: 40; sfail: 45;learned: false),
 (sname: 'Sanctuary'                   ;slevel: 11;smana: 10; sexp: 40; sfail: 45;learned: false),
 (sname: 'Create Food'                 ;slevel: 13;smana: 10; sexp: 50; sfail: 45;learned: false),
 (sname: 'Remove Curse'                ;slevel: 13;smana: 11; sexp: 50; sfail: 45;learned: false),
 (sname: 'Resist Heat and Cold'        ;slevel: 15;smana: 13; sexp: 60; sfail: 45;learned: false),
 (sname: 'Neutralize Poison'           ;slevel: 15;smana: 15; sexp: 60; sfail: 50;learned: false),
 (sname: 'Orb of Draining'             ;slevel: 17;smana: 15; sexp: 70; sfail: 50;learned: false),
 (sname: 'Cure Serious Wounds'         ;slevel: 17;smana: 15; sexp: 70; sfail: 50;learned: false),
 (sname: 'Sense Invisible'             ;slevel: 19;smana: 15; sexp: 75; sfail: 50;learned: false),
 (sname: 'Protection from Evil'        ;slevel: 19;smana: 15; sexp: 75; sfail: 50;learned: false),
 (sname: 'Earthquake'                  ;slevel: 21;smana: 17; sexp: 80; sfail: 50;learned: false),
 (sname: 'Sense Surroundings'          ;slevel: 23;smana: 17; sexp: 80; sfail: 50;learned: false),
 (sname: 'Cure Critical Wounds'        ;slevel: 25;smana: 20; sexp: 80; sfail: 50;learned: false),
 (sname: 'Turn Undead'                 ;slevel: 27;smana: 21; sexp: 90; sfail: 50;learned: false),
 (sname: 'Prayer'                      ;slevel: 29;smana: 22; sexp: 95; sfail: 50;learned: false),
 (sname: 'Dispell Undead'              ;slevel: 31;smana: 24;sexp: 100; sfail: 60;learned: false),
 (sname: 'Heal'                        ;slevel: 33;smana: 28;sexp: 125; sfail: 60;learned: false),
 (sname: 'Dispell Evil'                ;slevel: 35;smana: 32;sexp: 150; sfail: 70;learned: false),
 (sname: 'Glyph of Warding'            ;slevel: 37;smana: 36;sexp: 200; sfail: 90;learned: false),
 (sname: 'Holy Word'                   ;slevel: 39;smana: 38;sexp: 500; sfail: 95;learned: false)
					)
			);
	{ For Create Food spell use...          }
 mush :  treasure_type = 
(name: '& pint~ of fine grade mush'                      ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 1500;      cost: 0; subval: 308;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '1d1'  ;  level: 1);


	char_row	:  integer =  0;
	char_col        :  integer =  0;

	{ Initialize player generation variables			}
	sex_type  :  vtype =  'FemaleMale  ';

	{Race	STR,INT,WIS,DEX,CON,CHR,
		Ages, heights, and weights,
		Racial Bases for: dis,srh,stl,fos,bth,bthb,bsav,hitdie,
		infra, choice-classes                                   }

	race	:  
				  array [1..max_races] of race_type = 	(
		(trace: 'Human';     str_adj: 0;  int_adj: 0;  wis_adj: 0;  dex_adj: 0;  con_adj: 0;  chr_adj: 0;
			 b_age: 14;  m_age: 6; m_b_ht: 72;  m_m_ht: 6;m_b_wt: 180; m_m_wt: 25; f_b_ht: 66;  f_m_ht: 4;
			   f_b_wt: 120; f_m_wt: 20; b_exp: 1.00;
			  b_dis: 0;  srh: 0;  stl: 0;  fos: 0;  bth: 0;  bthb: 0;  bsav: 0; bhitdie: 10;  infra: 0;
			    tclass: %111111
			),
		(trace: 'Half-Elf'; str_adj: -1;  int_adj: 1;  wis_adj: 0;  dex_adj: 1; con_adj: -1;  chr_adj: 1;
			 b_age: 24; m_age: 16; m_b_ht: 66;  m_m_ht: 6;m_b_wt: 130; m_m_wt: 15; f_b_ht: 62;  f_m_ht: 6;
			   f_b_wt: 100; f_m_wt: 10; b_exp: 1.10;
			  b_dis: 2;  srh: 6;  stl: 1; fos: -1;  bth: 0;  bthb: 5;  bsav: 3;  bhitdie: 9;  infra: 0;
			    tclass: %111111
			),
		(trace: 'Elf';      str_adj: -1;  int_adj: 2;  wis_adj: 1;  dex_adj: 1; con_adj: -2;  chr_adj: 1;
			 b_age: 75; m_age: 75; m_b_ht: 60;  m_m_ht: 4;m_b_wt: 100;  m_m_wt: 6; f_b_ht: 54;  f_m_ht: 4;
			   f_b_wt: 80;  f_m_wt: 6; b_exp: 1.20;
			  b_dis: 5;  srh: 8;  stl: 1; fos: -2; bth: -5; bthb: 15;  bsav: 6;  bhitdie: 8;  infra: 0;
			    tclass: %011111
			),
		(trace: 'Halfling'; str_adj: -2;  int_adj: 2;  wis_adj: 1;  dex_adj: 3;  con_adj: 1;  chr_adj: 1;
			 b_age: 21; m_age: 12; m_b_ht: 36;  m_m_ht: 3; m_b_wt: 60;  m_m_wt: 3; f_b_ht: 33;  f_m_ht: 3;
			   f_b_wt: 50;  f_m_wt: 3; b_exp: 1.10;
			 b_dis: 15; srh: 12;  stl: 4; fos: -5;bth: -10; bthb: 20; bsav: 18;  bhitdie: 6;  infra: 4;
			   tclass: %001011
			),
		(trace: 'Gnome';    str_adj: -1;  int_adj: 2;  wis_adj: 0;  dex_adj: 2;  con_adj: 1; chr_adj: -2;
			 b_age: 50; m_age: 40; m_b_ht: 42;  m_m_ht: 3; m_b_wt: 90;  m_m_wt: 6; f_b_ht: 39;  f_m_ht: 3;
			   f_b_wt: 75;  f_m_wt: 3; b_exp: 1.25;
			 b_dis: 10;  srh: 6;  stl: 3; fos: -3; bth: -8; bthb: 12; bsav: 12;  bhitdie: 7;  infra: 3;
			   tclass: %001111
			),
		(trace: 'Dwarf';     str_adj: 2; int_adj: -3;  wis_adj: 1; dex_adj: -2;  con_adj: 2; chr_adj: -3;
			 b_age: 35; m_age: 15; m_b_ht: 48;  m_m_ht: 3;m_b_wt: 150; m_m_wt: 10; f_b_ht: 46;  f_m_ht: 3;
			   f_b_wt: 120; f_m_wt: 10; b_exp: 1.20;
			  b_dis: 2;  srh: 7;  stl: 0;  fos: 0; bth: 15;  bthb: 0;  bsav: 9;  bhitdie: 9;  infra: 5;
			    tclass: %000101
			),
		(trace: 'Half-Orc';  str_adj: 2; int_adj: -1;  wis_adj: 0;  dex_adj: 0;  con_adj: 1; chr_adj: -4;
			 b_age: 11;  m_age: 4; m_b_ht: 66;  m_m_ht: 1;m_b_wt: 150;  m_m_wt: 5; f_b_ht: 62;  f_m_ht: 1;
			   f_b_wt: 120;  f_m_wt: 5; b_exp: 1.10;
			 b_dis: -3;  srh: 0; stl: -1;  fos: 3; bth: 12; bthb: -5; bsav: -3; bhitdie: 10;  infra: 3;
			   tclass: %001101
			),
		(trace: 'Half-Troll';str_adj: 4; int_adj: -4; wis_adj: -2; dex_adj: -4;  con_adj: 3; chr_adj: -6;
			 b_age: 20; m_age: 10; m_b_ht: 96; m_m_ht: 10;m_b_wt: 300; m_m_wt: 50; f_b_ht: 84;  f_m_ht: 8;
			   f_b_wt: 260; f_m_wt: 40; b_exp: 1.20;
			 b_dis: -5; srh: -1; stl: -2;  fos: 5; bth: 20;bthb: -10; bsav: -8; bhitdie: 12;  infra: 3;
			   tclass: %000101
			)
		);

	{ Buying and selling adjustments for character race VS store	}
	{ owner race                                                    }

	rgold_adj :  
				  array [1..max_races] of
				  array [1..max_races] of real = 	(
			{  Hum,  HfE,  Elf,  Hal,  Gno,  Dwa,  HfO,  HfT}
{Human          }       ( 0.00, 0.05, 0.05, 0.10, 0.13, 0.15, 0.20, 0.25),
{Half-Elf       }       ( 0.10, 0.00, 0.00, 0.05, 0.10, 0.20, 0.25, 0.30),
{Elf            }       ( 0.10, 0.05, 0.00, 0.05, 0.10, 0.20, 0.25, 0.30),
{Halfling       }       ( 0.15, 0.10, 0.05,-0.05, 0.05, 0.10, 0.15, 0.30),
{Gnome          }       ( 0.15, 0.15, 0.10, 0.05,-0.05, 0.10, 0.15, 0.30),
{Dwarf          }       ( 0.15, 0.20, 0.20, 0.10, 0.10,-0.05, 0.25, 0.35),
{Half-Orc       }       ( 0.15, 0.20, 0.25, 0.15, 0.15, 0.30, 0.10, 0.15),
{Half-Troll     }       ( 0.10, 0.15, 0.15, 0.10, 0.10, 0.30, 0.10, 0.10)
			);

	{ Classes...							}
	class   :  
				  array [1..max_class] of class_type =       (
(title: 'Warrior'; m_exp: 0.00;  adj_hd: 9; mdis: 25; msrh: 14; mstl: 1; mfos: 38; mbth: 68; mbthb:
  55;msav: 30; madj_str: 5;madj_int: -2;madj_wis: -2; madj_dex: 2; madj_con: 2;madj_chr: -1;
  pspell: false;mspell: false),
(title: 'Mage';    m_exp: 0.30;  adj_hd: 0; mdis: 30; msrh: 16; mstl: 2; mfos: 36; mbth: 34; mbthb:
  20;msav: 20;madj_str: -5; madj_int: 3; madj_wis: 0; madj_dex: 0;madj_con: -2; madj_chr: 0;
  pspell: false;mspell: true ),
(title: 'Priest';  m_exp: 0.10;  adj_hd: 3; mdis: 25; msrh: 16; mstl: 2; mfos: 32; mbth: 48; mbthb:
  35;msav: 20; madj_str: 0;madj_int: -3; madj_wis: 3;madj_dex: -1; madj_con: 1; madj_chr: 2;
  pspell: true ;mspell: false),
(title: 'Rogue';   m_exp: 0.00;  adj_hd: 6; mdis: 45; msrh: 32; mstl: 4; mfos: 16; mbth: 60; mbthb:
  66;msav: 30; madj_str: 3; madj_int: 1;madj_wis: -2; madj_dex: 3; madj_con: 2;madj_chr: -1;
  pspell: false;mspell: true ),
(title: 'Ranger';  m_exp: 0.40;  adj_hd: 4; mdis: 30; msrh: 24; mstl: 3; mfos: 24; mbth: 56; mbthb:
  72;msav: 25; madj_str: 2; madj_int: 2; madj_wis: 0; madj_dex: 1; madj_con: 1; madj_chr: 1;
  pspell: false;mspell: true ),
(title: 'Paladin'; m_exp: 0.35;  adj_hd: 6; mdis: 20; msrh: 12; mstl: 1; mfos: 38; mbth: 70; mbthb:
  40;msav: 25; madj_str: 3;madj_int: -3; madj_wis: 1; madj_dex: 0; madj_con: 2; madj_chr: 2;
  pspell: true ;mspell: false)
			);

	{ Class titles for different levels				}
	player_title    :  
				  array [1..max_class] of
				  array [1..max_player_level] of btype =       (
	{ Warrior       }
('Novice','Veteran(1st)','Veteran(2nd)','Veteran(3rd)','Warrior(1st)',
'Warrior(2nd)','Warrior(3rd)','Swordsman-1','Swordsman-2','Swordsman-3',
'Hero','Swashbuckler','Myrmidon','Champion-1','Champion-2','Champion-3',
'Superhero','Knight','Superior Knt','Gallant Knt','Knt Errent','Keeper',
'Protector','Defender','Warder','Guardian Knt','Chevalier','Justiciar',
'Lord (1st)','Lord (2nd)','Lord (3rd)','Lord (4th)','Lord (5th)','Lord (6th)',
'Lord (7th)','Lord (8th)','Lord (9th)','Lord Gallant','Lord Keeper',
'Lord Noble'),
	{ Mage          }
('Novice','Apprentice','Trickster-1','Trickster-2','Trickster-3','Cabalist-1',
'Cabalist-2','Cabalist-3','Visionist','Phantasmist','Shadowist','Spellbinder',
'Illusionist','Evoker (1st)','Evoker (2nd)','Evoker (3rd)','Evoker (4th)',
'Conjurer','Theurgist','Thaumaturer','Magician','Enchanter','Warlock',
'Sorcerer','Necromancer','Mage (1st)','Mage (2nd)','Mage (3rd)','Mage (4th)',
'Mage (5th)','Wizard (1st)','Wizard (2nd)','Wizard (3rd)','Wizard (4th)',
'Wizard (5th)','Wizard (6th)','Wizard (7th)','Wizard (8th)','Wizard (9th)',
'Wizard Lord'),
	{ Priests       }
('Believer','Acolyte(1st)','Acolyte(2nd)','Acolyte(3rd)','Adept (1st)',
'Adept (2nd)','Adept (3rd)','Priest (1st)','Priest (2nd)','Priest (3rd)',
'Priest (4th)','Priest (5th)','Priest (6th)','Priest (7th)','Priest (8th)',
'Priest (9th)','Curate (1st)','Curate (2nd)','Curate (3rd)','Curate (4th)',
'Curate (5th)','Curate (6th)','Curate (7th)','Curate (8th)','Curate (9th)',
'Canon (1st)','Canon (2nd)','Canon (3rd)','Canon (4th)','Canon (5th)',
'Low Lama','Lama-1','Lama-2','Lama-3','High Lama','Great Lama','Patriarch',
'High Priest','Great Priest','Noble Priest'),
	{ Rogues        }
('Apprentice','Footpad','Cutpurse','Robber','Burglar','Filcher','Sharper',
'Magsman','Common Rogue','Rogue (1st)','Rogue (2nd)','Rogue (3rd)',
'Rogue (4th)','Rogue (5th)','Rogue (6th)','Rogue (7th)','Rogue (8th)',
'Rogue (9th)','Master Rogue','Expert Rogue','Senior Rogue','Chief Rogue',
'Prime Rogue','Low Thief','Thief (1st)','Thief (2nd)','Thief (3rd)',
'Thief (4th)','Thief (5th)','Thief (6th)','Thief (7th)','Thief (8th)',
'Thief (9th)','High Thief','Master Thief','Executioner','Low Assassin',
'Assassin','HighAssassin','Guildsmaster'),
	{ Rangers       }
('Runner (1st)','Runner (2nd)','Runner (3rd)','Strider (1st)','Strider (2nd)',
'Strider (3rd)','Scout (1st)','Scout (2nd)','Scout (3rd)','Scout (4th)',
'Scout (5th)','Courser (1st)','Courser (2nd)','Courser (3rd)','Courser (4th)',
'Courser (5th)','Tracker (1st)','Tracker (2nd)','Tracker (3rd)',
'Tracker (4th)','Tracker (5th)','Tracker (6th)','Tracker (7th)',
'Tracker (8th)','Tracker (9th)','Guide (1st)','Guide (2nd)','Guide (3rd)',
'Guide (4th)','Guide (5th)','Guide (6th)','Guide (7th)','Guide (8th)',
'Guide (9th)','Pathfinder-1','Pathfinder-2','Pathfinder-3','Ranger',
'High Ranger','Ranger Lord'),
	{ Paladins      }
('Gallant','Keeper (1st)','Keeper (2nd)','Keeper (3rd)','Keeper (4th)',
'Keeper (5th)','Keeper (6th)','Keeper (7th)','Keeper (8th)','Keeper (9th)',
'Protector-1','Protector-2','Protector-3','Protector-4','Protector-5',
'Protector-6','Protector-7','Protector-8','Defender-1','Defender-2',
'Defender-3','Defender-4','Defender-5','Defender-6','Defender-7','Defender-8',
'Warder (1st)','Warder (2nd)','Warder (3rd)','Warder (4th)','Warder (5th)',
'Warder (6th)','Warder (7th)','Warder (8th)','Warder (9th)','Gauardian',
'Chevalier','Justiciar','Paladin','High Lord')
				);
	{ Base experience levels, may be adjusted up for race and/or class}
	player_exp :  
				  array [1..max_player_level] of integer =    (
     10,     25,     45,     70,    100,    140,    200,    280,    380,   500,
    650,    850,   1100,   1400,   1800,   2300,   2900,   3600,   4400,  5400,
   6800,   8400,  10200,  12500,  17500,  25000,  35000,  50000,  75000,100000,
 150000, 200000, 300000, 400000, 500000, 750000,1500000,2500000,5000000,9999999
			);


	{ Background information					}
	background      :  
				  array [1..max_background] of background_type =       (
(info: 'You are the illegitimate and unacknowledged child ';           roll: 10; chart: 1; next: 2;
  bonus: -25),
(info: 'You are the illegitimate but acknowledged child ';             roll: 20; chart: 1; next: 2;
  bonus: -15),
(info: 'You are one of several children ';                             roll: 95; chart: 1; next: 2;
  bonus: -5),
(info: 'You are the 1st child ';                                      roll: 100; chart: 1; next: 2;
  bonus: 0),
(info: 'of a Serf.  ';                                                 roll: 40; chart: 2; next: 3;
  bonus: 15),
(info: 'of a Yeoman.  ';                                               roll: 65; chart: 2; next: 3;
  bonus: 30),
(info: 'of a Townsman.  ';                                             roll: 80; chart: 2; next: 3;
  bonus: 40),
(info: 'of a Guildsman.  ';                                            roll: 90; chart: 2; next: 3;
  bonus: 55),
(info: 'of a Landed Knight.  ';                                        roll: 96; chart: 2; next: 3;
  bonus: 70),
(info: 'of a Titled Noble.  ';                                         roll: 99; chart: 2; next: 3;
  bonus: 80),
(info: 'of a Royal Blood Line.  ';                                    roll: 100; chart: 2; next: 3;
  bonus: 90),
(info: 'You are the black sheep of the family.  ';                     roll: 20; chart: 3;next: 50;
  bonus: -30),
(info: 'You are a credit to the family.  ';                            roll: 80; chart: 3;next: 50;
  bonus: 5),
(info: 'You are a well liked child.  ';                               roll: 100; chart: 3;next: 50;
  bonus: 10),
(info: 'Your mother was a Green-Elf.  ';                               roll: 40; chart: 4; next: 1;
  bonus: 0),
(info: 'Your father was a Green-Elf.  ';                               roll: 75; chart: 4; next: 1;
  bonus: 5),
(info: 'Your mother was a Grey-Elf.  ';                                roll: 90; chart: 4; next: 1;
  bonus: 5),
(info: 'Your father was a Grey-Elf.  ';                                roll: 95; chart: 4; next: 1;
  bonus: 10),
(info: 'Your mother was a High-Elf.  ';                                roll: 98; chart: 4; next: 1;
  bonus: 15),
(info: 'Your father was a High-Elf.  ';                               roll: 100; chart: 4; next: 1;
  bonus: 20),
(info: 'You are one of several children ';                             roll: 60; chart: 7; next: 8;
  bonus: 0),
(info: 'You are the only child ';                                     roll: 100; chart: 7; next: 8;
  bonus: 5),
(info: 'of a Green-Elf ';                                              roll: 75; chart: 8; next: 9;
  bonus: 0),
(info: 'of a Grey-Elf ';                                               roll: 95; chart: 8; next: 9;
  bonus: 5),
(info: 'of a High-Elf ';                                              roll: 100; chart: 8; next: 9;
  bonus: 10),
(info: 'Ranger.  ';                                                    roll: 40; chart: 9;next: 54;
  bonus: 30),
(info: 'Archer.  ';                                                    roll: 70; chart: 9;next: 54;
  bonus: 40),
(info: 'Warrior.  ';                                                   roll: 87; chart: 9;next: 54;
  bonus: 60),
(info: 'Mage.  ';                                                      roll: 95; chart: 9;next: 54;
  bonus: 75),
(info: 'Prince.  ';                                                    roll: 99; chart: 9;next: 54;
  bonus: 90),
(info: 'King.  ';                                                     roll: 100; chart: 9;next: 54;
  bonus: 95),
(info: 'You are one of several children of a Halfling ';               roll: 85;chart: 10;next: 11;
  bonus: -5),
(info: 'You are the only child of a Halfling ';                       roll: 100;chart: 10;next: 11;
  bonus: 5),
(info: 'Bum.  ';                                                       roll: 20;chart: 11; next: 3;
  bonus: 5),
(info: 'Tavern Owner.  ';                                              roll: 30;chart: 11; next: 3;
  bonus: 30),
(info: 'Miller.  ';                                                    roll: 40;chart: 11; next: 3;
  bonus: 40),
(info: 'Home Owner.  ';                                                roll: 50;chart: 11; next: 3;
  bonus: 50),
(info: 'Burglar.  ';                                                   roll: 80;chart: 11; next: 3;
  bonus: 60),
(info: 'Warrior.  ';                                                   roll: 95;chart: 11; next: 3;
  bonus: 65),
(info: 'Mage.  ';                                                     roll: 100;chart: 11; next: 3;
  bonus: 75),
(info: 'Clan Elder.  ';                                               roll: 100;chart: 11; next: 3;
  bonus: 90),
(info: 'You are one of several children of a Gnome ';                  roll: 85;chart: 13;next: 14;
  bonus: -5),
(info: 'You are the only child of a Gnome ';                          roll: 100;chart: 13;next: 14;
  bonus: 5),
(info: 'Beggar.  ';                                                    roll: 20;chart: 14; next: 3;
  bonus: 5),
(info: 'Bragart.  ';                                                   roll: 50;chart: 14; next: 3;
  bonus: 20),
(info: 'Prankster.  ';                                                 roll: 75;chart: 14; next: 3;
  bonus: 35),
(info: 'Warrior.  ';                                                   roll: 95;chart: 14; next: 3;
  bonus: 50),
(info: 'Mage.  ';                                                     roll: 100;chart: 14; next: 3;
  bonus: 75),
(info: 'You are one of two children of a Dwarven ';                    roll: 25;chart: 16;next: 17;
  bonus: -10),
(info: 'You are the only child of a Dwarven ';                        roll: 100;chart: 16;next: 17;
  bonus: 0),
(info: 'Thief.  ';                                                     roll: 10;chart: 17;next: 18;
  bonus: 10),
(info: 'Prison Guard.  ';                                              roll: 25;chart: 17;next: 18;
  bonus: 25),
(info: 'Miner.  ';                                                     roll: 75;chart: 17;next: 18;
  bonus: 40),
(info: 'Warrior.  ';                                                   roll: 90;chart: 17;next: 18;
  bonus: 60),
(info: 'Priest.  ';                                                    roll: 99;chart: 17;next: 18;
  bonus: 80),
(info: 'King.  ';                                                     roll: 100;chart: 17;next: 18;
  bonus: 100),
(info: 'You are the black sheep of the family.  ';                     roll: 15;chart: 18;next: 57;
  bonus: -40),
(info: 'You are a credit to the family.  ';                            roll: 85;chart: 18;next: 57;
  bonus: 0),
(info: 'You are a well liked child.  ';                               roll: 100;chart: 18;next: 57;
  bonus: 5),
(info: 'Your mother was an Orc, but it is unacknowledged.  ';          roll: 25;chart: 19;next: 20;
  bonus: -25),
(info: 'Your father was an Orc, but it is unacknowledged.  ';         roll: 100;chart: 19;next: 20;
  bonus: -25),
(info: 'You are the adopted child ';                                  roll: 100;chart: 20; next: 2;
  bonus: 0),
(info: 'Your mother was a Cave-Troll ';                                roll: 30;chart: 22;next: 23;
  bonus: -30),
(info: 'Your father was a Cave-Troll ';                                roll: 60;chart: 22;next: 23;
  bonus: -25),
(info: 'Your mother was a Hill-Troll ';                                roll: 75;chart: 22;next: 23;
  bonus: -20),
(info: 'Your father was a Hill-Troll ';                                roll: 90;chart: 22;next: 23;
  bonus: -15),
(info: 'Your mother was a Water-Troll ';                               roll: 95;chart: 22;next: 23;
  bonus: -10),
(info: 'Your father was a Water-Troll ';                              roll: 100;chart: 22;next: 23;
  bonus: -5),
(info: 'Cook.  ';                                                       roll: 5;chart: 23;next: 62;
  bonus: 10),
(info: 'Warrior.  ';                                                   roll: 95;chart: 23;next: 62;
  bonus: 5),
(info: 'Shaman.  ';                                                    roll: 99;chart: 23;next: 62;
  bonus: 15),
(info: 'Clan Chief.  ';                                               roll: 100;chart: 23;next: 62;
  bonus: 30),
(info: 'You have dark brown eyes, ';                                   roll: 20;chart: 50;next: 51;
  bonus: 0),
(info: 'You have brown eyes, ';                                        roll: 60;chart: 50;next: 51;
  bonus: 0),
(info: 'You have hazel eyes, ';                                        roll: 70;chart: 50;next: 51;
  bonus: 0),
(info: 'You have green eyes, ';                                        roll: 80;chart: 50;next: 51;
  bonus: 0),
(info: 'You have blue eyes, ';                                         roll: 90;chart: 50;next: 51;
  bonus: 0),
(info: 'You have blue-gray eyes, ';                                   roll: 100;chart: 50;next: 51;
  bonus: 0),
(info: 'straight ';                                                    roll: 70;chart: 51;next: 52;
  bonus: 0),
(info: 'wavey ';                                                       roll: 90;chart: 51;next: 52;
  bonus: 0),
(info: 'curly ';                                                      roll: 100;chart: 51;next: 52;
  bonus: 0),
(info: 'black hair, ';                                                 roll: 30;chart: 52;next: 53;
  bonus: 0),
(info: 'brown hair, ';                                                 roll: 70;chart: 52;next: 53;
  bonus: 0),
(info: 'auburn hair, ';                                                roll: 80;chart: 52;next: 53;
  bonus: 0),
(info: 'red hair, ';                                                   roll: 90;chart: 52;next: 53;
  bonus: 0),
(info: 'blonde hair, ';                                               roll: 100;chart: 52;next: 53;
  bonus: 0),
(info: 'and a very dark complexion.';                                  roll: 10;chart: 53;next: -1;
  bonus: 0),
(info: 'and a dark complexion.';                                       roll: 30;chart: 53;next: -1;
  bonus: 0),
(info: 'and an average complexion.';                                   roll: 80;chart: 53;next: -1;
  bonus: 0),
(info: 'and a fair complexion.';                                       roll: 90;chart: 53;next: -1;
  bonus: 0),
(info: 'and a very fair complexion.';                                 roll: 100;chart: 53;next: -1;
  bonus: 0),
(info: 'You have light grey eyes, ';                                   roll: 85;chart: 54;next: 55;
  bonus: 0),
(info: 'You have light blue eyes, ';                                   roll: 95;chart: 54;next: 55;
  bonus: 0),
(info: 'You have light green eyes, ';                                 roll: 100;chart: 54;next: 55;
  bonus: 0),
(info: 'straight ';                                                    roll: 75;chart: 55;next: 56;
  bonus: 0),
(info: 'wavey ';                                                      roll: 100;chart: 55;next: 56;
  bonus: 0),
(info: 'black hair, and a fair complexion.';                           roll: 75;chart: 56;next: -1;
  bonus: 0),
(info: 'brown hair, and a fair complexion.';                           roll: 85;chart: 56;next: -1;
  bonus: 0),
(info: 'blonde hair, and a fair complexion.';                          roll: 95;chart: 56;next: -1;
  bonus: 0),
(info: 'silver hair, and a fair complexion.';                         roll: 100;chart: 56;next: -1;
  bonus: 0),
(info: 'You have dark brown eyes, ';                                   roll: 99;chart: 57;next: 58;
  bonus: 0),
(info: 'You have glowing red eyes, ';                                 roll: 100;chart: 57;next: 58;
  bonus: 10),
(info: 'straight ';                                                    roll: 90;chart: 58;next: 59;
  bonus: 0),
(info: 'wavey ';                                                      roll: 100;chart: 58;next: 59;
  bonus: 0),
(info: 'black hair, ';                                                 roll: 75;chart: 59;next: 60;
  bonus: 0),
(info: 'brown hair, ';                                                roll: 100;chart: 59;next: 60;
  bonus: 0),
(info: 'a one foot beard, ';                                           roll: 25;chart: 60;next: 61;
  bonus: 0),
(info: 'a two foot beard, ';                                           roll: 60;chart: 60;next: 61;
  bonus: 1),
(info: 'a three foot beard, ';                                         roll: 90;chart: 60;next: 61;
  bonus: 3),
(info: 'a four foot beard, ';                                         roll: 100;chart: 60;next: 61;
  bonus: 5),
(info: 'and a dark complexion.';                                      roll: 100;chart: 61;next: -1;
  bonus: 0),
(info: 'You have slime green eyes, ';                                  roll: 60;chart: 62;next: 63;
  bonus: 0),
(info: 'You have puke yellow eyes, ';                                  roll: 85;chart: 62;next: 63;
  bonus: 0),
(info: 'You have blue-bloodshot eyes, ';                               roll: 99;chart: 62;next: 63;
  bonus: 0),
(info: 'You have glowing red eyes, ';                                 roll: 100;chart: 62;next: 63;
  bonus: 5),
(info: 'dirty ';                                                       roll: 33;chart: 63;next: 64;
  bonus: 0),
(info: 'mangy ';                                                       roll: 66;chart: 63;next: 64;
  bonus: 0),
(info: 'oily ';                                                       roll: 100;chart: 63;next: 64;
  bonus: 0),
(info: 'sea-weed green hair, ';                                        roll: 33;chart: 64;next: 65;
  bonus: 0),
(info: 'bright red hair, ';                                            roll: 66;chart: 64;next: 65;
  bonus: 0),
(info: 'dark purple hair, ';                                          roll: 100;chart: 64;next: 65;
  bonus: 0),
(info: 'and green ';                                                   roll: 25;chart: 65;next: 66;
  bonus: 0),
(info: 'and blue ';                                                    roll: 50;chart: 65;next: 66;
  bonus: 0),
(info: 'and white ';                                                   roll: 75;chart: 65;next: 66;
  bonus: 0),
(info: 'and black ';                                                  roll: 100;chart: 65;next: 66;
  bonus: 0),
(info: 'ulcerous skin.';                                               roll: 33;chart: 66;next: -1;
  bonus: 0),
(info: 'scabby skin.';                                                 roll: 66;chart: 66;next: -1;
  bonus: 0),
(info: 'leprous skin.';                                               roll: 100;chart: 66;next: -1;
  bonus: 0)
			);


	{ Treasure related values					}
	inven_ctr       :  
				  integer =  0;
	inven_weight    :  
				  integer =  0;
	missle_ctr      :  
					  integer =  0;
	equip_ctr       :  
				  integer =  0;
	blank_treasure  :  treasure_type =  (name: ' ';tval: 0;tchar: ' ';flags: 0;p1: 0;cost: 0;subval: 0;
	  weight: 0;number: 0;tohit: 0;todam: 0;ac: 0;toac: 0;damage: ' ';level: 0);

	{ Gold list (All types of gold and gems are defined here)	}
	gold_list       :  
				  array [1..max_gold]    of treasure_type =       (
(name: 'copper'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 3;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'copper'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 4;   subval: 2;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'copper'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 5;   subval: 3;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'silver'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 6;   subval: 4;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'silver'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 7;   subval: 5;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'silver'                                          ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;      cost: 8;   subval: 6;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'garnets'                                         ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;      cost: 9;   subval: 7;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'garnets'                                         ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 8;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'gold'                                            ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;     cost: 12;   subval: 9;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'gold'                                            ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;     cost: 14;   subval: 0;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'gold'                                            ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;     cost: 16;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'opals'                                           ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 18;   subval: 2;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'saphires'                                        ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 20;   subval: 3;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'gold'                                            ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;     cost: 24;   subval: 4;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'rubies'                                          ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 28;   subval: 5;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'diamonds'                                        ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 32;   subval: 6;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'emeralds'                                        ; tval: 100; tchar: '*';flags:
  $00000000;
    p1: 0;     cost: 40;   subval: 7;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1),
(name: 'mithril'                                         ; tval: 100; tchar: '$';flags:
  $00000000;
    p1: 0;     cost: 80;   subval: 8;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: ' '    ;  level: 1)
				);

	{ Object description:  Objects are defined here.  Each object has
	the following attributes:
		Descriptor : Name of item and formats.
			%C is replaced with a random color.
			%W is replaced with a random wood.
			%M is replaced with a random metal.
			%R is replaced with a random rock.
			%P1 is replaced with the number in P1 (see below).
			%P2 is replaced with plus-to-hit.
			%P3 is replaced with plus-to-damage.
			%P4 is replaced with plus-to-AC.
			%P5 is replaced with number in P1, no sign.
			& is replaced with 'a', 'an', or a number.
			~ is replaced with null or 's'.
		Character  : Character that represents the item.
		Type value : Value representing the type of object.
			1   ~   Miscellaneous Object.
			2   &   chest.
			10  (Left Curly Brace)  sling ammo.
			11  (Left Curly Brace)  bolt.
			12  (Left Curly Brace)  arrow.
			13  ~   spike.
			15  ~   Lamp or Torch.
			20  (Right curly brace)  bow, crossbow, or sling.
			21  /   hafted weapon.
			22  \   pole arm.
			23  |   sword or dagger.
			30  ]   boots.
			31  ]   gloves and gauntlets.
			32  (   Cloak
			33  ]   helm.
			34  )   shield.
			35  [   hard armor.
			36  (   soft armor.
			40  "   amulet.
			45  =   ring.
			55  _   staff.
			60  -   rod.
			65  -   wand.
			70  ?   scroll.
			71  ?   scroll.    continued
			75  !   potion.
			76  !   potion.    continued
			77  !   flask of oil.
			80  ,   food.
			90  ?   Magic Book.
			91  ?   Prayer Book.
			100 $   valuable metal.
			100 *   valuable gems.
			101 .   Unseen trap.
			102 ^   Seen trap.
			103 :   Rubble.
			104 '   Open door.
			105 +   Closed door.
			107 <   Up staircase.
			108 >   Down staircase.
			109 #   Secret door.
			110 1,2,3,4,5,6   Entrance to store.

		Sub value  : separate value for each item of a type.
		Damage     : amount of damage item can cause.
		Weight     : relative weight of an item.
		Number     : number of items appearing in group.
			If items can be added together then
				subval > 255
			If items are considered one unit when added
			together then
				subval > 511
		To hit     : magical pluses to hit.
		To damage  : magical pluses to damage.
		AC         : objects relative armor class.
			1 is worse than 5 is worse than 10 ect...
		To AC      : Magical bonuses to AC.
		P1         : Catch all for magical abilities such as
			     pluses to strength, minuses to searching...
		Flags      : Abilities of object.  Each abilitiy is a
			     bit.  Bits 1-31 are used. (Signed integer)

		Flags used for anything that can be worn or wielded:
				Bit #   Hex #           Ability
				1       00000001        Strength
				2       00000002        Dexterity
				3       00000004        Constitution
				4       00000008        Intelligence
				5       00000010        Wisdom
				6       00000020        Charisma
				7       00000040        Searching
				8       00000080        Slow digestion
				9       00000100        Stealth
				10      00000200        Aggravation
				11      00000400        Teleportation
				12      00000800        Regeneration
				13      00001000        Speed
				14      00002000        Slay Dragon
				15      00004000        Slay Monster
				16      00008000        Slay Evil
				17      00010000        Slay Undead
				18      00020000        Cold Brand
				19      00040000        Flame Brand
				20      00080000        Resist Fire
				21      00100000        Resist Acid
				22      00200000        Resist Cold
				23      00400000        Sustain Stat (P1)
				24      00800000        Free Action
				25      01000000        See Invisible
				26      02000000        Resist Lightning
				27      04000000        Feather Fall
				28      08000000        Blindness
				29      10000000        Timidness
				30      20000000        Tunneling
				31      40000000        Infra vision
				32      80000000        Cursed
		Level      : Minimum level on which item can be found.
		Cost       : Relative cost of item.

		Special Abilities can be added to item by MAGIC_INIT,
		found in MISC.INC.

	Scrolls, Potions, and Food:
		Flags is used to define a function which reading/quaffing
		will cause.  Most scrolls and potions have only one bit
		set.  Potions will generally have some food value, found
		in P1.

	Wands and Staffs:
		Flags defines a function, P1 contains number of charges
		for item.  P1 is set in MAGIC_INIT (MISC.INC)

	Chests:
		Traps are added randomly by MAGIC.INIT in MISC.INC.
	}
	{ Object list (All objects must be defined here)                }
	object_list     :  
				  array [1..max_objects] of treasure_type =       (
(name: '& %M Mushroom~| of Poison'                       ;  tval: 80; tchar: ',';flags:
  $00000001;
  p1: 500;      cost: 0; subval: 257;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %M Mushroom~| of Blindness'                    ;  tval: 80; tchar: ',';flags:
  $00000002;
  p1: 500;      cost: 0; subval: 258;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 9),
(name: '& %M Mushroom~| of Paranoia'                     ;  tval: 80; tchar: ',';flags:
  $00000004;
  p1: 500;      cost: 0; subval: 259;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 9),
(name: '& %M Mushroom~| of Confusion'                    ;  tval: 80; tchar: ',';flags:
  $00000008;
  p1: 500;      cost: 0; subval: 260;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %M Mushroom~| of Halucination'                 ;  tval: 80; tchar: ',';flags:
  $00000010;
  p1: 500;      cost: 0; subval: 261;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 13),
(name: '& %M Mushroom~| of Cure Poison'                  ;  tval: 80; tchar: ',';flags:
  $00000020;
  p1: 500;     cost: 60; subval: 262;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 8),
(name: '& %M Mushroom~| of Cure Blindness'               ;  tval: 80; tchar: ',';flags:
  $00000040;
  p1: 500;     cost: 50; subval: 263;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 10),
(name: '& %M Mushroom~| of Cure Paranoia'                ;  tval: 80; tchar: ',';flags:
  $00000080;
  p1: 500;     cost: 25; subval: 264;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 12),
(name: '& %M Mushroom~| of Cure Confusion'               ;  tval: 80; tchar: ',';flags:
  $00000100;
  p1: 500;     cost: 50; subval: 265;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 6),
(name: '& %M Mushroom~| of Weakness'                     ;  tval: 80; tchar: ',';flags:
  $04000200;
  p1: 500;      cost: 0; subval: 266;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %M Mushroom~| of Unhealth'                     ;  tval: 80; tchar: ',';flags:
  $04000400;
  p1: 500;     cost: 50; subval: 267;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '10d10'; level: 15),
(name: '& %M Mushroom~| of Restore Constitution'         ;  tval: 80; tchar: ',';flags:
  $00010000;
  p1: 500;    cost: 350; subval: 268;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 20),
(name: '& %M Mushroom~| of First-Aid'                    ;  tval: 80; tchar: ',';flags:
  $00200000;
  p1: 500;      cost: 5; subval: 269;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 6),
(name: '& %M Mushroom~| of Minor Cures'                  ;  tval: 80; tchar: ',';flags:
  $00400000;
  p1: 500;     cost: 20; subval: 270;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %M Mushroom~| of Light Cures'                  ;  tval: 80; tchar: ',';flags:
  $00800000;
  p1: 500;     cost: 30; subval: 271;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 10),
(name: '& %M Mushroom~| of Restoring'                    ;  tval: 80; tchar: ',';flags:
  $001F8040;
  p1: 500;   cost: 1000; subval: 272;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ; level: 30),
(name: '& Hairy %M Mold~| of Poison'                     ;  tval: 80; tchar: ',';flags:
  $00000001;
 p1: 1200;      cost: 0; subval: 273;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 15),
(name: '& Hairy %M Mold~| of Halucinations'              ;  tval: 80; tchar: ',';flags:
  $00000010;
 p1: 1200;      cost: 0; subval: 274;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 18),
(name: '& Hairy %M Mold~| of Cure Poison'                ;  tval: 80; tchar: ',';flags:
  $00000020;
 p1: 1200;     cost: 75; subval: 275;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 19),
(name: '& Hairy %M Mold~| of Unhealth'                   ;  tval: 80; tchar: ',';flags:
  $00000400;
 p1: 1200;     cost: 25; subval: 276;   weight: 1;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '6d8'  ; level: 28),
(name: '& Hairy %M Mold~| of Cure Serious Wounds'        ;  tval: 80; tchar: ',';flags:
  $02000000;
 p1: 1200;     cost: 75; subval: 277;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 16),
(name: '& Ration~ of Food'                               ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 5000;      cost: 3; subval: 307;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 0),
(name: '& Ration~ of Food'                               ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 5000;      cost: 3; subval: 307;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Ration~ of Food'                               ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 5000;      cost: 3; subval: 307;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 10),
(name: '& Slime Mold~'                                   ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 3000;      cost: 2; subval: 308;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Piece~ of Elvish Waybread'                     ;  tval: 80; tchar: ',';flags:
  $02000020;
 p1: 7500;     cost: 10; subval: 313;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 6),
(name: '& Piece~ of Elvish Waybread'                     ;  tval: 80; tchar: ',';flags:
  $02000020;
 p1: 7500;     cost: 10; subval: 313;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 12),
(name: '& Piece~ of Elvish Waybread'                     ;  tval: 80; tchar: ',';flags:
  $02000020;
 p1: 7500;     cost: 10; subval: 313;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ; level: 20),
(name: '& Dagger (Main Gauche)^ (%P2,%P3)'               ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 25;   subval: 1;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d5'  ;  level: 2),
(name: '& Dagger (Misercorde)^ (%P2,%P3)'                ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 2;  weight: 15;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0),
(name: '& Dagger (Stiletto)^ (%P2,%P3)'                  ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 3;  weight: 12;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0),
(name: '& Dagger (Bodkin)^ (%P2,%P3)'                    ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 4;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 1),
(name: '& Broken dagger^ (%P2,%P3)'                      ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 5;  weight: 15;   number: 1;  tohit: -2;  todam: -2;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& Backsword^ (%P2,%P3)'                          ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 60;   subval: 6;  weight: 95;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d9'  ;  level: 7),
(name: '& Bastard Sword^ (%P2,%P3)'                      ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 350;   subval: 7; weight: 140;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ; level: 14),
(name: '& Thrusting Sword (Bilbo)^ (%P2,%P3)'            ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 60;   subval: 8;  weight: 80;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 4),
(name: '& Thrusting Sword (Baselard)^ (%P2,%P3)'         ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 80;   subval: 9; weight: 100;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d7'  ;  level: 5),
(name: '& Broadsword^ (%P2,%P3)'                         ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 255;  subval: 10; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ;  level: 9),
(name: '& Two Handed Sword (Claymore)^ (%P2,%P3)'        ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 775;  subval: 11; weight: 200;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d6'  ; level: 30),
(name: '& Cutlass^ (%P2,%P3)'                            ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 85;  subval: 12; weight: 110;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d7'  ;  level: 7),
(name: '& Two Handed Sword (Espadon)^ (%P2,%P3)'         ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 655;  subval: 13; weight: 180;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d6'  ; level: 35),
(name: '& Executioner''s Sword^ (%P2,%P3)'               ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 850;  subval: 14; weight: 260;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d5'  ; level: 40),
(name: '& Two Handed Sword (Flamberge)^ (%P2,%P3)'       ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;   cost: 1000;  subval: 15; weight: 240;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d5'  ; level: 45),
(name: '& Foil^ (%P2,%P3)'                               ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 35;  subval: 16;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d5'  ;  level: 2),
(name: '& Katana^ (%P2,%P3)'                             ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 400;  subval: 17; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ; level: 18),
(name: '& Longsword^ (%P2,%P3)'                          ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 300;  subval: 18; weight: 130;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d10' ; level: 12),
(name: '& Two Handed Sword (No-Dachi)^ (%P2,%P3)'        ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 675;  subval: 19; weight: 200;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d4'  ; level: 45),
(name: '& Rapier^ (%P2,%P3)'                             ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 42;  subval: 20;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 4),
(name: '& Sabre^ (%P2,%P3)'                              ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 50;  subval: 21;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d7'  ;  level: 5),
(name: '& Small Sword^ (%P2,%P3)'                        ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 48;  subval: 22;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 5),
(name: '& Two Handed Sword (Zweihander)^ (%P2,%P3)'      ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;   cost: 1000;  subval: 23; weight: 280;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d6'  ; level: 50),
(name: '& Broken sword^ (%P2,%P3)'                       ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 24;  weight: 75;   number: 1;  tohit: -2;  todam: -2;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& Battle Axe (Balestarius)^ (%P2,%P3)'           ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 500;   subval: 1; weight: 180;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d8'  ; level: 30),
(name: '& Ball and Chain^ (%P2,%P3)'                     ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 200;   subval: 2; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d4'  ; level: 20),
(name: '& Battle Axe (European)^ (%P2,%P3)'              ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 334;   subval: 3; weight: 170;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ; level: 13),
(name: '& Broad Axe^ (%P2,%P3)'                          ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 304;   subval: 4; weight: 160;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 17),
(name: '& Cat-O-Nine Tails^ (%P2,%P3)'                   ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;     cost: 14;   subval: 5;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 3),
(name: '& Wooden Club^ (%P2,%P3)'                        ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 6; weight: 100;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ;  level: 0),
(name: '& Flail^ (%P2,%P3)'                              ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 353;   subval: 7; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 12),
(name: '& Two Handed Great Flail^ (%P2,%P3)'             ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 590;   subval: 8; weight: 280;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d6'  ; level: 45),
(name: '& Morningstar^ (%P2,%P3)'                        ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 396;   subval: 9; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 10),
(name: '& Mace^ (%P2,%P3)'                               ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 130;  subval: 10; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d4'  ;  level: 6),
(name: '& War Hammer^ (%P2,%P3)'                         ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 225;  subval: 11; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d3'  ;  level: 5),
(name: '& Mace (Lead filled)^ (%P2,%P3)'                 ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 502;  subval: 12; weight: 180;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ; level: 15),
(name: '& Awl-Pike^ (%P2,%P3)'                           ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 340;   subval: 1; weight: 160;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ;  level: 8),
(name: '& Beaked Axe^ (%P2,%P3)'                         ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 408;   subval: 2; weight: 180;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 15),
(name: '& Fauchard^ (%P2,%P3)'                           ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 376;   subval: 3; weight: 170;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d10' ; level: 17),
(name: '& Glaive^ (%P2,%P3)'                             ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 363;   subval: 4; weight: 190;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 20),
(name: '& Halberd^ (%P2,%P3)'                            ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 430;   subval: 5; weight: 190;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ; level: 22),
(name: '& Lucerne Hammer^ (%P2,%P3)'                     ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 376;   subval: 6; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ; level: 11),
(name: '& Pike^ (%P2,%P3)'                               ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 358;   subval: 7; weight: 160;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ; level: 15),
(name: '& Spear^ (%P2,%P3)'                              ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;     cost: 36;   subval: 8;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 5),
(name: '& Lance^ (%P2,%P3)'                              ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 230;   subval: 9; weight: 300;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d8'  ; level: 10),
(name: '& Javelin^ (%P2,%P3)'                            ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;     cost: 18;  subval: 10;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 4),
(name: '& Short Bow^ (%P2)'                              ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 2;     cost: 50;   subval: 1;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 3),
(name: '& Long Bow^ (%P2)'                               ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 3;    cost: 120;   subval: 2;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 10),
(name: '& Composite Bow^ (%P2)'                          ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 4;    cost: 240;   subval: 3;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 40),
(name: '& Light Crossbow^ (%P2)'                         ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 5;    cost: 140;  subval: 10; weight: 110;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 15),
(name: '& Heavy Crossbow^ (%P2)'                         ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 6;    cost: 300;  subval: 11; weight: 200;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 30),
(name: '& Sling^ (%P2)'                                  ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 1;      cost: 5;  subval: 20;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Arrow~^ (%P2,%P3)'                             ;  tval: 12; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 1;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 2),
(name: '& Bolt~^ (%P2,%P3)'                              ;  tval: 11; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 2;   subval: 1;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d5'  ;  level: 2),
(name: '& Rounded Pebble~^ (%P2,%P3)'                    ;  tval: 10; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 1;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 0),
(name: '& Iron Shot~^ (%P2,%P3)'                         ;  tval: 10; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 2;   subval: 1;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ;  level: 3),
(name: '& Iron Spike~'                                   ;  tval: 13; tchar: '~';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Brass Lantern~ with %P5 turns of light'        ;  tval: 15; tchar: '~';flags:
  $00000000;
 p1: 7500;     cost: 35;   subval: 1;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Wooden Torch~ with %P5 turns of light'         ;  tval: 15; tchar: '~';flags:
  $00000000;
 p1: 4000;      cost: 2;  subval: 13;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Orcish Pick^ (%P1) (%P2,%P3)'                  ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 2;    cost: 500;   subval: 2; weight: 180;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ; level: 20),
(name: '& Dwarven Pick^ (%P1) (%P2,%P3)'                 ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 3;   cost: 1200;   subval: 3; weight: 200;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ; level: 50),
(name: '& Gnomish Shovel^ (%P1) (%P2,%P3)'               ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 1;    cost: 100;   subval: 5;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 20),
(name: '& Dwarven Shovel^ (%P1) (%P2,%P3)'               ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 2;    cost: 250;   subval: 6; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ; level: 40),
(name: '& Pair of Soft Leather Shoes^ [%P6,%P4]'         ;  tval: 30; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 4;   subval: 1;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Pair of Soft Leather Boots^ [%P6,%P4]'         ;  tval: 30; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 7;   subval: 2;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ;  level: 4),
(name: '& Pair of Hard Leather Boots^ [%P6,%P4]'         ;  tval: 30; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 12;   subval: 3;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d1'  ;  level: 6),
(name: '& Soft Leather Cap^ [%P6,%P4]'                   ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 4;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 2),
(name: '& Hard Leather Cap^ [%P6,%P4]'                   ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 12;   subval: 2;  weight: 15;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '0d0'  ;  level: 4),
(name: '& Metal Cap^ [%P6,%P4]'                          ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 30;   subval: 3;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d1'  ;  level: 7),
(name: '& Iron Helm^ [%P6,%P4]'                          ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 75;   subval: 4;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 5;
      toac: 0; damage: '1d3'  ; level: 20),
(name: '& Steel Helm^ [%P6,%P4]'                         ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;    cost: 200;   subval: 5;  weight: 60;   number: 1;   tohit: 0;   todam: 0;   ac: 6;
      toac: 0; damage: '1d3'  ; level: 40),
(name: '& Silver Crown^ (%P1)'                           ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;    cost: 250;   subval: 6;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 44),
(name: '& Golden Crown^ (%P1)'                           ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;    cost: 500;   subval: 7;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 47),
(name: '& Jewel Encrusted Crown^ (%P1)'                  ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;   cost: 1000;   subval: 8;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 50),
(name: '& Robe^ [%P6,%P4]'                               ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;      cost: 4;   subval: 1;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: 'Soft Leather Armor^ [%P6,%P4]'                   ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 18;   subval: 2;  weight: 80;   number: 1;   tohit: 0;   todam: 0;   ac: 4;
      toac: 0; damage: '0d0'  ;  level: 2),
(name: 'Soft Studded Leather^ [%P6,%P4]'                 ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 35;   subval: 3;  weight: 90;   number: 1;   tohit: 0;   todam: 0;   ac: 5;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: 'Hard Leather Armor^ [%P6,%P4]'                   ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 55;   subval: 4; weight: 100;   number: 1;  tohit: -1;   todam: 0;   ac: 6;
      toac: 0; damage: '1d1'  ;  level: 5),
(name: 'Hard Studded Leather^ [%P6,%P4]'                 ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 100;   subval: 5; weight: 110;   number: 1;  tohit: -1;   todam: 0;   ac: 7;
      toac: 0; damage: '1d2'  ;  level: 7),
(name: 'Woven Cord Armor^ [%P6,%P4]'                     ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 45;   subval: 6; weight: 150;   number: 1;  tohit: -1;   todam: 0;   ac: 6;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: 'Soft Leather Ring Mail^ [%P6,%P4]'               ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 160;   subval: 7; weight: 130;   number: 1;  tohit: -1;   todam: 0;   ac: 6;
      toac: 0; damage: '1d2'  ; level: 10),
(name: 'Hard Leather Ring Mail^ [%P6,%P4]'               ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 230;   subval: 8; weight: 150;   number: 1;  tohit: -2;   todam: 0;   ac: 8;
      toac: 0; damage: '1d3'  ; level: 12),
(name: 'Leather Scale Mail^ [%P6,%P4]'                   ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 330;   subval: 9; weight: 140;   number: 1;  tohit: -1;   todam: 0;  ac: 11;
      toac: 0; damage: '1d1'  ; level: 14),
(name: 'Metal Scale Mail^ [%P6,%P4]'                     ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 430;   subval: 1; weight: 250;   number: 1;  tohit: -2;   todam: 0;  ac: 13;
      toac: 0; damage: '1d4'  ; level: 24),
(name: 'Chain Mail^ [%P6,%P4]'                           ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 530;   subval: 2; weight: 220;   number: 1;  tohit: -2;   todam: 0;  ac: 14;
      toac: 0; damage: '1d4'  ; level: 26),
(name: 'Rusty Chain Mail^ [%P6,%P4]'                     ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 3; weight: 200;   number: 1;  tohit: -5;   todam: 0;  ac: 14;
      toac: -8; damage: '1d4'  ; level: 26),
(name: 'Double Chain Mail^ [%P6,%P4]'                    ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 630;   subval: 4; weight: 260;   number: 1;  tohit: -2;   todam: 0;  ac: 15;
      toac: 0; damage: '1d4'  ; level: 28),
(name: 'Augmented Chain Mail^ [%P6,%P4]'                 ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 675;   subval: 5; weight: 270;   number: 1;  tohit: -2;   todam: 0;  ac: 16;
      toac: 0; damage: '1d4'  ; level: 30),
(name: 'Bar Chain Mail^ [%P6,%P4]'                       ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 720;   subval: 6; weight: 280;   number: 1;  tohit: -2;   todam: 0;  ac: 18;
      toac: 0; damage: '1d4'  ; level: 34),
(name: 'Metal Brigandine Armor^ [%P6,%P4]'               ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 775;   subval: 7; weight: 290;   number: 1;  tohit: -3;   todam: 0;  ac: 19;
      toac: 0; damage: '1d4'  ; level: 36),
(name: 'Laminated Armor^ [%P6,%P4]'                      ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 825;   subval: 8; weight: 300;   number: 1;  tohit: -3;   todam: 0;  ac: 20;
      toac: 0; damage: '1d4'  ; level: 38),
(name: 'Partial Plate Armor^ [%P6,%P4]'                  ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 900;   subval: 9; weight: 260;   number: 1;  tohit: -3;   todam: 0;  ac: 22;
      toac: 0; damage: '1d6'  ; level: 42),
(name: 'Metal Lamellar Armor^ [%P6,%P4]'                 ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 950;  subval: 10; weight: 340;   number: 1;  tohit: -3;   todam: 0;  ac: 23;
      toac: 0; damage: '1d6'  ; level: 44),
(name: 'Full Plate Armor^ [%P6,%P4]'                     ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;   cost: 1050;  subval: 11; weight: 380;   number: 1;  tohit: -3;   todam: 0;  ac: 25;
      toac: 0; damage: '2d4'  ; level: 48),
(name: 'Ribbed Plate Armor^ [%P6,%P4]'                   ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;   cost: 1200;  subval: 12; weight: 380;   number: 1;  tohit: -3;   todam: 0;  ac: 28;
      toac: 0; damage: '2d4'  ; level: 50),
(name: '& Cloak^ [%P6,%P4]'                              ;  tval: 32; tchar: '(';flags:
  $00000000;
    p1: 0;      cost: 3;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Set of Leather Gloves^ [%P6,%P4]'              ;  tval: 31; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 3;   subval: 1;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Set of Gauntlets^ [%P6,%P4]'                   ;  tval: 31; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 35;   subval: 2;  weight: 25;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ; level: 12),
(name: '& Small Leather Shield^ [%P6,%P4]'               ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 30;   subval: 1;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& Medium Leather Shield^ [%P6,%P4]'              ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 60;   subval: 2;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d2'  ;  level: 8),
(name: '& Large Leather Shield^ [%P6,%P4]'               ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;    cost: 120;   subval: 3; weight: 100;   number: 1;   tohit: 0;   todam: 0;   ac: 4;
      toac: 0; damage: '1d2'  ; level: 15),
(name: '& Small Metal Shield^ [%P6,%P4]'                 ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 50;   subval: 4;  weight: 65;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& Medium Metal Shield^ [%P6,%P4]'                ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;    cost: 125;   subval: 5;  weight: 90;   number: 1;   tohit: 0;   todam: 0;   ac: 4;
      toac: 0; damage: '1d3'  ; level: 20),
(name: '& Large Metal Shield^ [%P6,%P4]'                 ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;    cost: 200;   subval: 6; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 5;
      toac: 0; damage: '1d3'  ; level: 30),
(name: '& %R Ring| of Gain Strength^ (%P1)'              ;  tval: 45; tchar: '=';flags:
  $00000001;
    p1: 0;    cost: 400;   subval: 1;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 30),
(name: '& %R Ring| of Gain Dexterity^ (%P1)'             ;  tval: 45; tchar: '=';flags:
  $00000002;
    p1: 0;    cost: 400;   subval: 2;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 30),
(name: '& %R Ring| of Gain Constitution^ (%P1)'          ;  tval: 45; tchar: '=';flags:
  $00000004;
    p1: 0;    cost: 400;   subval: 3;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 30),
(name: '& %R Ring| of Gain Intelligence^ (%P1)'          ;  tval: 45; tchar: '=';flags:
  $00000008;
    p1: 0;    cost: 350;   subval: 4;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 30),
(name: '& %R Ring| of Speed^ (%P1)'                      ;  tval: 45; tchar: '=';flags:
  $00001000;
    p1: 0;   cost: 3000;   subval: 7;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& %R Ring| of Searching^ (%P1)'                  ;  tval: 45; tchar: '=';flags:
  $00000040;
    p1: 0;    cost: 250;   subval: 8;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Teleportation^'                     ;  tval: 45; tchar: '=';flags:
  $80000400;
    p1: 0;      cost: 0;   subval: 9;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Slow Digestion^'                   ;  tval: 45; tchar: '=';flags:
  $00000080;
    p1: 0;    cost: 250;  subval: 10;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Resist Fire^'                      ;  tval: 45; tchar: '=';flags:
  $00080000;
    p1: 0;    cost: 250;  subval: 11;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 14),
(name: '& %R Ring| of Resist Cold^'                      ;  tval: 45; tchar: '=';flags:
  $00200000;
    p1: 0;    cost: 250;  subval: 12;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 14),
(name: '& %R Ring| of Feather Falling^'                  ;  tval: 45; tchar: '=';flags:
  $04000000;
    p1: 0;    cost: 200;  subval: 13;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Adornment^'                        ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;     cost: 20;  subval: 14;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Adornment^'                        ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;     cost: 30;  subval: 15;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Weakness^'                         ;  tval: 45; tchar: '=';flags:
  $00000001;
   p1: -5;      cost: 0;  subval: 16;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Lordly Protection (FIRE)^'         ;  tval: 45; tchar: '=';flags:
  $00080000;
    p1: 0;   cost: 1200;  subval: 17;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 5; damage: '0d0'  ; level: 50),
(name: '& %R Ring| of Lordly Protection (ACID)^'         ;  tval: 45; tchar: '=';flags:
  $00100000;
    p1: 0;   cost: 1200;  subval: 18;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 5; damage: '0d0'  ; level: 50),
(name: '& %R Ring| of Lordly Protection (COLD)^'         ;  tval: 45; tchar: '=';flags:
  $00200000;
    p1: 0;   cost: 1200;  subval: 19;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 5; damage: '0d0'  ; level: 50),
(name: '& %R Ring| of WOE^'                              ;  tval: 45; tchar: '=';flags:
  $80000640;
   p1: -5;      cost: 0;  subval: 20;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: -3; damage: '0d0'  ; level: 50),
(name: '& %R Ring| of Stupidity^'                        ;  tval: 45; tchar: '=';flags:
  $80000008;
   p1: -5;      cost: 0;  subval: 21;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '0d0'  ; level: 20),
(name: '& %R Ring| of Increase Damage^ (%P3)'            ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;    cost: 100;  subval: 22;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 20),
(name: '& %R Ring| of Increase To-Hit^ (%P2)'            ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;    cost: 100;  subval: 23;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 20),
(name: '& %R Ring| of Protection^ [%P4]'                 ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;    cost: 100;  subval: 24;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Aggravate Monster^'                ;  tval: 45; tchar: '=';flags:
  $80000200;
    p1: 0;      cost: 0;  subval: 25;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of See Invisible^'                    ;  tval: 45; tchar: '=';flags:
  $01000000;
    p1: 0;    cost: 340;  subval: 26;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 40),
(name: '& %R Ring| of Sustain Strength^'                 ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 1;    cost: 750;  subval: 27;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 44),
(name: '& %R Ring| of Sustain Intelligence^'             ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 2;    cost: 600;  subval: 28;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 44),
(name: '& %R Ring| of Sustain Wisdom^'                   ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 3;    cost: 600;  subval: 29;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 44),
(name: '& %R Ring| of Sustain Constitution^'             ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 4;    cost: 750;  subval: 30;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 44),
(name: '& %R Ring| of Sustain Dexterity^'                ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 5;    cost: 750;  subval: 31;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 44),
(name: '& %R Ring| of Sustain Charisma^'                 ;  tval: 45; tchar: '=';flags:
  $00400000;
    p1: 6;    cost: 500;  subval: 32;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& %R Ring| of Slaying^'                          ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 6;   cost: 1000;  subval: 33;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& %A Amulet| of Adornment^'                      ;  tval: 40; tchar: '"';flags:
  $00000000;
    p1: 0;     cost: 20;  subval: 11;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 16),
(name: '& %A Amulet| of Adornment^'                      ;  tval: 40; tchar: '"';flags:
  $00000000;
    p1: 0;     cost: 30;  subval: 12;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 16),
(name: '& %A Amulet| of Wisdom^ (%P1)'                   ;  tval: 40; tchar: '"';flags:
  $00000010;
    p1: 0;    cost: 300;   subval: 5;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 20),
(name: '& %A Amulet| of Charisma^ (%P1)'                 ;  tval: 40; tchar: '"';flags:
  $00000020;
    p1: 0;    cost: 250;   subval: 6;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 20),
(name: '& %A Amulet| of Searching^ (%P1)'                ;  tval: 40; tchar: '"';flags:
  $00000040;
    p1: 0;    cost: 250;   subval: 7;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 14),
(name: '& %A Amulet| of Teleportation^'                   ;  tval: 40; tchar: '"';flags:
  $80000400;
    p1: 0;      cost: 0;   subval: 8;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 14),
(name: '& %A Amulet| of Slow Digestion^'                 ;  tval: 40; tchar: '"';flags:
  $00000080;
    p1: 0;    cost: 200;   subval: 9;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 14),
(name: '& %A Amulet| of Resist Acid^'                    ;  tval: 40; tchar: '"';flags:
  $00100000;
    p1: 0;    cost: 300;  subval: 10;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 24),
(name: '& %A Amulet| of the Magi^'                       ;  tval: 40; tchar: '"';flags:
  $01800040;
    p1: 0;   cost: 5000;  subval: 13;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 3; damage: '0d0'  ; level: 50),
(name: '& %A Amulet| of DOOM^'                           ;  tval: 40; tchar: '"';flags:
  $8000007F;
   p1: -5;      cost: 0;  subval: 14;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Enchant Weapon To-Hit'          ;  tval: 70; tchar: '?';flags:
  $00000001;
    p1: 0;    cost: 125; subval: 257;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Enchant Weapon To-Dam'          ;  tval: 70; tchar: '?';flags:
  $00000002;
    p1: 0;    cost: 125; subval: 258;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Enchant Armor'                  ;  tval: 70; tchar: '?';flags:
  $00000004;
    p1: 0;    cost: 125; subval: 259;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Identify'                       ;  tval: 70; tchar: '?';flags:
  $00000008;
    p1: 0;     cost: 50; subval: 260;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Identify'                       ;  tval: 70; tchar: '?';flags:
  $00000008;
    p1: 0;     cost: 50; subval: 260;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Identify'                       ;  tval: 70; tchar: '?';flags:
  $00000008;
    p1: 0;     cost: 50; subval: 260;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 10),
(name: '& Scroll~ %T| of Remove Curse'                   ;  tval: 70; tchar: '?';flags:
  $00000010;
    p1: 0;    cost: 100; subval: 261;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& Scroll~ %T| of Light'                          ;  tval: 70; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 262;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: '& Scroll~ %T| of Light'                          ;  tval: 70; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 262;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 3),
(name: '& Scroll~ %T| of Light'                          ;  tval: 70; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 262;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 7),
(name: '& Scroll~ %T| of Summon Monster'                 ;  tval: 70; tchar: '?';flags:
  $00000040;
    p1: 0;      cost: 0; subval: 263;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Phase Door'                     ;  tval: 70; tchar: '?';flags:
  $00000080;
    p1: 0;     cost: 15; subval: 264;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Teleport'                       ;  tval: 70; tchar: '?';flags:
  $00000100;
    p1: 0;     cost: 40; subval: 265;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 10),
(name: '& Scroll~ %T| of Teleport Level'                 ;  tval: 70; tchar: '?';flags:
  $00000200;
    p1: 0;     cost: 50; subval: 266;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 20),
(name: '& Scroll~ %T| of Monster Confusion'              ;  tval: 70; tchar: '?';flags:
  $00000400;
    p1: 0;     cost: 30; subval: 267;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Magic Mapping'                  ;  tval: 70; tchar: '?';flags:
  $00000800;
    p1: 0;     cost: 40; subval: 268;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Sleep Monster'                  ;  tval: 70; tchar: '?';flags:
  $00001000;
    p1: 0;     cost: 35; subval: 269;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Rune of Protection'             ;  tval: 70; tchar: '?';flags:
  $00002000;
    p1: 0;    cost: 500; subval: 270;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Treasure Detection'             ;  tval: 70; tchar: '?';flags:
  $00004000;
    p1: 0;     cost: 15; subval: 271;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: '& Scroll~ %T| of Object Detection'               ;  tval: 70; tchar: '?';flags:
  $00008000;
    p1: 0;     cost: 15; subval: 272;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: '& Scroll~ %T| of Trap Detection'                 ;  tval: 70; tchar: '?';flags:
  $00010000;
    p1: 0;     cost: 35; subval: 273;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Trap Detection'                 ;  tval: 70; tchar: '?';flags:
  $00010000;
    p1: 0;     cost: 35; subval: 273;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 8),
(name: '& Scroll~ %T| of Trap Detection'                 ;  tval: 70; tchar: '?';flags:
  $00010000;
    p1: 0;     cost: 35; subval: 273;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Door/Stair Location'            ;  tval: 70; tchar: '?';flags:
  $00020000;
    p1: 0;     cost: 35; subval: 274;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Door/Stair Location'            ;  tval: 70; tchar: '?';flags:
  $00020000;
    p1: 0;     cost: 35; subval: 274;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 10),
(name: '& Scroll~ %T| of Door/Stair Location'            ;  tval: 70; tchar: '?';flags:
  $00020000;
    p1: 0;     cost: 35; subval: 274;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 15),
(name: '& Scroll~ %T| of Mass Genocide'                  ;  tval: 70; tchar: '?';flags:
  $00040000;
    p1: 0;   cost: 1000; subval: 275;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Detect Invisible'               ;  tval: 70; tchar: '?';flags:
  $00080000;
    p1: 0;     cost: 15; subval: 276;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Aggravate Monster'              ;  tval: 70; tchar: '?';flags:
  $00100000;
    p1: 0;      cost: 0; subval: 277;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Trap Creation'                  ;  tval: 70; tchar: '?';flags:
  $00200000;
    p1: 0;      cost: 0; subval: 278;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Trap/Door Destruction'          ;  tval: 70; tchar: '?';flags:
  $00400000;
    p1: 0;     cost: 50; subval: 279;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Door Creation'                  ;  tval: 70; tchar: '?';flags:
  $00800000;
    p1: 0;    cost: 100; subval: 280;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Recharging'                     ;  tval: 70; tchar: '?';flags:
  $01000000;
    p1: 0;    cost: 200; subval: 281;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 40),
(name: '& Scroll~ %T| of Genocide'                       ;  tval: 70; tchar: '?';flags:
  $02000000;
    p1: 0;    cost: 750; subval: 282;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 35),
(name: '& Scroll~ %T| of Darkness'                       ;  tval: 70; tchar: '?';flags:
  $04000000;
    p1: 0;      cost: 0; subval: 283;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Protection from Evil'           ;  tval: 70; tchar: '?';flags:
  $08000000;
    p1: 0;     cost: 50; subval: 284;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 30),
(name: '& Scroll~ %T| of Create Food'                    ;  tval: 70; tchar: '?';flags:
  $10000000;
    p1: 0;     cost: 10; subval: 285;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of Dispell Undead'                 ;  tval: 70; tchar: '?';flags:
  $20000000;
    p1: 0;    cost: 200; subval: 286;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 40),
(name: '& Scroll~ %T| of *Enchant Weapon*'               ;  tval: 71; tchar: '?';flags:
  $00000001;
    p1: 0;    cost: 500; subval: 257;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Curse Weapon'                   ;  tval: 71; tchar: '?';flags:
  $00000002;
    p1: 0;      cost: 0; subval: 258;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of *Enchant Armor*'                ;  tval: 71; tchar: '?';flags:
  $00000004;
    p1: 0;    cost: 500; subval: 259;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Curse Armor'                    ;  tval: 71; tchar: '?';flags:
  $00000008;
    p1: 0;      cost: 0; subval: 260;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 50),
(name: '& Scroll~ %T| of Summon Undead'                  ;  tval: 71; tchar: '?';flags:
  $00000010;
    p1: 0;      cost: 0; subval: 261;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 15),
(name: '& Scroll~ %T| of Blessing'                       ;  tval: 71; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 262;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 1),
(name: '& Scroll~ %T| of Holy Chant'                     ;  tval: 71; tchar: '?';flags:
  $00000040;
    p1: 0;     cost: 40; subval: 263;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 12),
(name: '& Scroll~ %T| of Holy Prayer'                    ;  tval: 71; tchar: '?';flags:
  $00000080;
    p1: 0;     cost: 80; subval: 264;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 24),
(name: '& Scroll~ %T| of Word-of-Recall'                 ;  tval: 71; tchar: '?';flags:
  $00000100;
    p1: 0;    cost: 150; subval: 265;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 5),
(name: '& Scroll~ %T| of *Destruction*'                  ;  tval: 71; tchar: '?';flags:
  $00000200;
    p1: 0;    cost: 250; subval: 266;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ; level: 40),
(name: '& %C Potion~| of Gain Strength'                  ;  tval: 75; tchar: '!';flags:
  $00000001;
    p1: 0;    cost: 200; subval: 257;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Poison'                         ;  tval: 75; tchar: '!';flags:
  $00000002;
    p1: 0;      cost: 0; subval: 258;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& %C Potion~| of Restore Strength'               ;  tval: 75; tchar: '!';flags:
  $00000004;
    p1: 0;    cost: 300; subval: 259;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Gain Intelligence'              ;  tval: 75; tchar: '!';flags:
  $00000008;
    p1: 0;    cost: 300; subval: 260;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Lose Intelligence'              ;  tval: 75; tchar: '!';flags:
  $00000010;
    p1: 0;      cost: 0; subval: 261;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Restore Intelligence'           ;  tval: 75; tchar: '!';flags:
  $00000020;
    p1: 0;    cost: 300; subval: 262;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Gain Wisdom'                    ;  tval: 75; tchar: '!';flags:
  $00000040;
    p1: 0;    cost: 300; subval: 263;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Lose Wisdom'                    ;  tval: 75; tchar: '!';flags:
  $00000080;
    p1: 0;      cost: 0; subval: 264;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Restore Wisdom'                 ;  tval: 75; tchar: '!';flags:
  $00000100;
    p1: 0;    cost: 300; subval: 265;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Charisma'                       ;  tval: 75; tchar: '!';flags:
  $00000200;
    p1: 0;    cost: 300; subval: 266;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Ugliness'                       ;  tval: 75; tchar: '!';flags:
  $00000400;
    p1: 0;      cost: 0; subval: 267;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Restore Charisma'               ;  tval: 75; tchar: '!';flags:
  $00000800;
    p1: 0;    cost: 300; subval: 268;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Cure Light Wounds'              ;  tval: 75; tchar: '!';flags:
  $10001000;
   p1: 50;     cost: 15; subval: 269;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Cure Light Wounds'              ;  tval: 75; tchar: '!';flags:
  $10001000;
   p1: 50;     cost: 15; subval: 269;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Cure Light Wounds'              ;  tval: 75; tchar: '!';flags:
  $10001000;
   p1: 50;     cost: 15; subval: 269;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %C Potion~| of Cure Serious Wounds'            ;  tval: 75; tchar: '!';flags:
  $30002000;
  p1: 100;     cost: 40; subval: 270;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 3),
(name: '& %C Potion~| of Cure Critical Wounds'           ;  tval: 75; tchar: '!';flags:
  $70004000;
  p1: 100;    cost: 100; subval: 271;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 5),
(name: '& %C Potion~| of Healing'                        ;  tval: 75; tchar: '!';flags:
  $70008000;
  p1: 200;    cost: 200; subval: 272;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ; level: 12),
(name: '& %C Potion~| of Gain Constitution'              ;  tval: 75; tchar: '!';flags:
  $00010000;
    p1: 0;    cost: 300; subval: 273;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Gain Experience'                ;  tval: 75; tchar: '!';flags:
  $00020000;
    p1: 0;   cost: 2500; subval: 274;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 50),
(name: '& %C Potion~| of Sleep'                          ;  tval: 75; tchar: '!';flags:
  $10040000;
  p1: 100;      cost: 0; subval: 275;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Blindness'                      ;  tval: 75; tchar: '!';flags:
  $00080000;
    p1: 0;      cost: 0; subval: 276;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Confusion'                      ;  tval: 75; tchar: '!';flags:
  $00100000;
   p1: 50;      cost: 0; subval: 277;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Poison'                         ;  tval: 75; tchar: '!';flags:
  $00200000;
    p1: 0;      cost: 0; subval: 278;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& %C Potion~| of Haste Self'                     ;  tval: 75; tchar: '!';flags:
  $00400000;
    p1: 0;     cost: 75; subval: 279;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Slowness'                       ;  tval: 75; tchar: '!';flags:
  $00800000;
   p1: 50;      cost: 0; subval: 280;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Icky Green Potion~| of Slime Mold Juice'       ;  tval: 75; tchar: '!';flags:
  $30000000;
  p1: 400;      cost: 2; subval: 281;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0),
(name: '& Light Brown Potion~| of Apple Juice'           ;  tval: 75; tchar: '!';flags:
  $00000000;
  p1: 250;      cost: 1; subval: 282;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0),
(name: '& Clear Potion~| of Water'                       ;  tval: 75; tchar: '!';flags:
  $00000000;
  p1: 200;      cost: 0; subval: 283;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Gain Dexterity'                 ;  tval: 75; tchar: '!';flags:
  $02000000;
    p1: 0;    cost: 300; subval: 284;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| of Restore Dexterity'              ;  tval: 75; tchar: '!';flags:
  $04000000;
    p1: 0;    cost: 300; subval: 285;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Restore Constitution'           ;  tval: 75; tchar: '!';flags:
  $68000000;
    p1: 0;    cost: 300; subval: 286;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Learning'                       ;  tval: 76; tchar: '!';flags:
  $00000001;
    p1: 0;    cost: 200; subval: 287;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 45),
(name: '& %C Potion~| of Lose Memories'                  ;  tval: 76; tchar: '!';flags:
  $00000002;
    p1: 0;      cost: 0; subval: 288;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 10),
(name: '& %C Potion~| of Salt Water'                     ;  tval: 76; tchar: '!';flags:
  $00000004;
    p1: 0;      cost: 0; subval: 289;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& %C Potion~| of Invulnerability'                ;  tval: 76; tchar: '!';flags:
  $00000008;
    p1: 0;    cost: 250; subval: 290;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Heroism'                        ;  tval: 76; tchar: '!';flags:
  $00000010;
    p1: 0;     cost: 35; subval: 291;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Super Heroism'                  ;  tval: 76; tchar: '!';flags:
  $00000020;
    p1: 0;    cost: 100; subval: 292;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& %C Potion~| of Boldliness'                     ;  tval: 76; tchar: '!';flags:
  $00000040;
    p1: 0;     cost: 10; subval: 293;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Restore Life Levels'            ;  tval: 76; tchar: '!';flags:
  $00000080;
    p1: 0;    cost: 400; subval: 294;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %C Potion~| of Resist Heat'                    ;  tval: 76; tchar: '!';flags:
  $00000100;
    p1: 0;     cost: 30; subval: 295;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Resist Cold'                    ;  tval: 76; tchar: '!';flags:
  $00000200;
    p1: 0;     cost: 30; subval: 296;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Detect Invisible'               ;  tval: 76; tchar: '!';flags:
  $00000400;
    p1: 0;     cost: 50; subval: 297;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& %C Potion~| of Slow Poison'                    ;  tval: 76; tchar: '!';flags:
  $00000800;
    p1: 0;     cost: 25; subval: 298;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& %C Potion~| of Neutralize Poison'              ;  tval: 76; tchar: '!';flags:
  $00001000;
    p1: 0;     cost: 75; subval: 299;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 5),
(name: '& %C Potion~| of Restore Mana'                   ;  tval: 76; tchar: '!';flags:
  $00002000;
    p1: 0;     cost: 35; subval: 300;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %C Potion~| Infra-Vision'                      ;  tval: 76; tchar: '!';flags:
  $00004000;
    p1: 0;     cost: 20; subval: 301;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 3),
(name: '& Flask~ of oil'                                 ;  tval: 77; tchar: '!';flags:
  $00040000;
 p1: 7500;      cost: 3; subval: 257;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '2d6'  ;  level: 1),
(name: '& %M Wand| of Light^ (%P1 charges)'              ;  tval: 65; tchar: '-';flags:
  $00000001;
    p1: 0;    cost: 200;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Lightning Bolts^ (%P1 charges)'    ;  tval: 65; tchar: '-';flags:
  $00000002;
    p1: 0;    cost: 600;   subval: 2;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 15),
(name: '& %M Wand| of Frost Bolts^ (%P1 charges)'        ;  tval: 65; tchar: '-';flags:
  $00000004;
    p1: 0;    cost: 800;   subval: 3;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 20),
(name: '& %M Wand| of Fire Bolts^ (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00000008;
    p1: 0;   cost: 1000;   subval: 4;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 30),
(name: '& %M Wand| of Stone-to-Mud^ (%P1 charges)'       ;  tval: 65; tchar: '-';flags:
  $00000010;
    p1: 0;    cost: 300;   subval: 5;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 12),
(name: '& %M Wand| of Polymorph^ (%P1 charges)'          ;  tval: 65; tchar: '-';flags:
  $00000020;
    p1: 0;    cost: 400;   subval: 6;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 20),
(name: '& %M Wand| of Heal Monster^ (%P1 charges)'       ;  tval: 65; tchar: '-';flags:
  $00000040;
    p1: 0;      cost: 0;   subval: 7;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Haste Monster^ (%P1 charges)'      ;  tval: 65; tchar: '-';flags:
  $00000080;
    p1: 0;      cost: 0;   subval: 8;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Slow Monster^ (%P1 charges)'       ;  tval: 65; tchar: '-';flags:
  $00000100;
    p1: 0;    cost: 500;   subval: 9;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Confuse Monster^ (%P1 charges)'    ;  tval: 65; tchar: '-';flags:
  $00000200;
    p1: 0;    cost: 400;  subval: 10;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Sleep Monster^ (%P1 charges)'      ;  tval: 65; tchar: '-';flags:
  $00000400;
    p1: 0;    cost: 500;  subval: 11;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 7),
(name: '& %M Wand| of Drain Life^ (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00000800;
    p1: 0;   cost: 1200;  subval: 12;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 50),
(name: '& %M Wand| of Trap/Door destruction^ (%P1 charges)';  tval: 65; tchar: '-';flags:
  $00001000;
    p1: 0;    cost: 100;  subval: 13;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 12),
(name: '& %M Wand| of Magic Missile^ (%P1 charges)'       ;  tval: 65; tchar: '-';flags:
  $00002000;
    p1: 0;    cost: 200;  subval: 14;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Wall Building^ (%P1 charges)'      ;  tval: 65; tchar: '-';flags:
  $00004000;
    p1: 0;    cost: 400;  subval: 15;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 25),
(name: '& %M Wand| of Clone Monster^ (%P1 charges)'      ;  tval: 65; tchar: '-';flags:
  $00008000;
    p1: 0;      cost: 0;  subval: 16;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %M Wand| of Teleport Away^ (%P1 charges)'      ;  tval: 65; tchar: '-';flags:
  $00010000;
    p1: 0;    cost: 350;  subval: 17;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 20),
(name: '& %M Wand| of Disarming^ (%P1 charges)'          ;  tval: 65; tchar: '-';flags:
  $00020000;
    p1: 0;    cost: 700;  subval: 18;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 20),
(name: '& %M Wand| of Lightning Balls^ (%P1 charges)'    ;  tval: 65; tchar: '-';flags:
  $00040000;
    p1: 0;   cost: 1200;  subval: 19;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 35),
(name: '& %M Wand| of Cold Balls^ (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00080000;
    p1: 0;   cost: 1500;  subval: 20;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& %M Wand| of Fire Balls^ (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00100000;
    p1: 0;   cost: 1800;  subval: 21;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 50),
(name: '& %M Wand| of Stinking Cloud^ (%P1 charges)'     ;  tval: 65; tchar: '-';flags:
  $00200000;
    p1: 0;    cost: 400;  subval: 22;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 5),
(name: '& %M Wand| of Acid Balls^ (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00400000;
    p1: 0;   cost: 1650;  subval: 23;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 48),
(name: '& %M Wand| of Wonder^ (%P1 charges)'             ;  tval: 65; tchar: '-';flags:
  $00800000;
    p1: 0;    cost: 250;  subval: 24;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2),
(name: '& %W Staff| of Light^ (%P1 charges)'             ;  tval: 55; tchar: '_';flags:
  $00000001;
    p1: 0;    cost: 250;   subval: 1;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& %W Staff| of Door/Stair Location^ (%P1 charges)';  tval: 55; tchar: '_';flags:
  $00000002;
    p1: 0;    cost: 350;   subval: 2;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Trap Location^ (%P1 charges)'     ;  tval: 55; tchar: '_';flags:
  $00000004;
    p1: 0;    cost: 350;   subval: 3;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Treasure Location^ (%P1 charges)' ;  tval: 55; tchar: '_';flags:
  $00000008;
    p1: 0;    cost: 200;   subval: 4;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& %W Staff| of Object Location^ (%P1 charges)'   ;  tval: 55; tchar: '_';flags:
  $00000010;
    p1: 0;    cost: 200;   subval: 5;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& %W Staff| of Teleportation^ (%P1 charges)'     ;  tval: 55; tchar: '_';flags:
  $00000020;
    p1: 0;    cost: 400;   subval: 6;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 20),
(name: '& %W Staff| of Earthquakes^ (%P1 charges)'       ;  tval: 55; tchar: '_';flags:
  $00000040;
    p1: 0;    cost: 350;   subval: 7;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 40),
(name: '& %W Staff| of Summoning^ (%P1 charges)'         ;  tval: 55; tchar: '_';flags:
  $00000080;
    p1: 0;      cost: 0;   subval: 8;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Summoning^ (%P1 charges)'         ;  tval: 55; tchar: '_';flags:
  $00000080;
    p1: 0;      cost: 0;   subval: 8;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 50),
(name: '& %W Staff| of *Destruction*^ (%P1 charges)'     ;  tval: 55; tchar: '_';flags:
  $00000200;
    p1: 0;   cost: 2500;  subval: 10;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 50),
(name: '& %W Staff| of Starlite^ (%P1 charges)'          ;  tval: 55; tchar: '_';flags:
  $00000400;
    p1: 0;    cost: 800;  subval: 11;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 20),
(name: '& %W Staff| of Haste Monsters^ (%P1 charges)'    ;  tval: 55; tchar: '_';flags:
  $00000800;
    p1: 0;      cost: 0;  subval: 12;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Slow Monsters^ (%P1 charges)'     ;  tval: 55; tchar: '_';flags:
  $00001000;
    p1: 0;    cost: 800;  subval: 13;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Sleep Monsters^ (%P1 charges)'    ;  tval: 55; tchar: '_';flags:
  $00002000;
    p1: 0;    cost: 700;  subval: 14;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 10),
(name: '& %W Staff| of Cure Light Wounds^ (%P1 charges)' ;  tval: 55; tchar: '_';flags:
  $00004000;
    p1: 0;    cost: 350;  subval: 15;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& %W Staff| of Detect Invisible^ (%P1 charges)'  ;  tval: 55; tchar: '_';flags:
  $00008000;
    p1: 0;    cost: 200;  subval: 16;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& %W Staff| of Speed^ (%P1 charges)'             ;  tval: 55; tchar: '_';flags:
  $00010000;
    p1: 0;    cost: 800;  subval: 17;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 40),
(name: '& %W Staff| of Slowness^ (%P1 charges)'          ;  tval: 55; tchar: '_';flags:
  $00020000;
    p1: 0;      cost: 0;  subval: 18;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 40),
(name: '& %W Staff| of Mass Polymorph^ (%P1 charges)'    ;  tval: 55; tchar: '_';flags:
  $00040000;
    p1: 0;    cost: 750;  subval: 19;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 46),
(name: '& %W Staff| of Remove Curse^ (%P1 charges)'      ;  tval: 55; tchar: '_';flags:
  $00080000;
    p1: 0;    cost: 500;  subval: 20;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 47),
(name: '& %W Staff| of Detect Evil^ (%P1 charges)'       ;  tval: 55; tchar: '_';flags:
  $00100000;
    p1: 0;    cost: 350;  subval: 21;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 20),
(name: '& %W Staff| of Curing^ (%P1 charges)'            ;  tval: 55; tchar: '_';flags:
  $00200000;
    p1: 0;   cost: 1000;  subval: 22;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 25),
(name: '& %W Staff| of Dispell Evil^ (%P1 charges)'      ;  tval: 55; tchar: '_';flags:
  $00400000;
    p1: 0;   cost: 1200;  subval: 23;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 49),
(name: '& %W Staff| of Darkness^ (%P1 charges)'          ;  tval: 55; tchar: '_';flags:
  $01000000;
    p1: 0;      cost: 0;  subval: 25;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ; level: 50),
(name: '& %W Staff| of Darkness^ (%P1 charges)'          ;  tval: 55; tchar: '_';flags:
  $01000000;
    p1: 0;      cost: 0;  subval: 25;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 5),
(name: '& Book of Magic Spells [Beginners-Magik]'        ;  tval: 90; tchar: '?';flags:
  $0000007F;
    p1: 0;     cost: 25; subval: 257;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Book of Magic Spells [Magik I]'                ;  tval: 90; tchar: '?';flags:
  $0000FF80;
    p1: 0;    cost: 100; subval: 258;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Book of Magic Spells [Magik II]'               ;  tval: 90; tchar: '?';flags:
  $00FF0000;
    p1: 0;    cost: 400; subval: 259;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Book of Magic Spells [The Mages Guide to Power]';  tval: 90; tchar: '?';flags:
  $7F000000;
    p1: 0;    cost: 800; subval: 261;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Holy Book of Prayers [Beginners Handbook]'     ;  tval: 91; tchar: '?';flags:
  $000000FF;
    p1: 0;     cost: 25; subval: 258;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Holy Book of Prayers [Words of Wisdom]'        ;  tval: 91; tchar: '?';flags:
  $0000FF00;
    p1: 0;    cost: 100; subval: 259;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Holy Book of Prayers [Chants and Blessings]'   ;  tval: 91; tchar: '?';flags:
  $01FF0000;
    p1: 0;    cost: 300; subval: 260;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Holy Book of Prayers [Exorcism and Dispelling]';  tval: 91; tchar: '?';flags:
  $7E000000;
    p1: 0;    cost: 900; subval: 261;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 40),
(name: '& Small wooden chest'                            ;   tval: 2; tchar: '&';flags:
  $0F000000;
    p1: 0;     cost: 20;   subval: 1; weight: 250;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d3'  ;  level: 7),
(name: '& Large wooden chest'                            ;   tval: 2; tchar: '&';flags:
  $15000000;
    p1: 0;     cost: 60;   subval: 4; weight: 500;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ; level: 15),
(name: '& Small iron chest'                              ;   tval: 2; tchar: '&';flags:
  $0F000000;
    p1: 0;    cost: 100;   subval: 7; weight: 300;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d4'  ; level: 25),
(name: '& Large iron chest'                              ;   tval: 2; tchar: '&';flags:
  $1F000000;
    p1: 0;    cost: 150;  subval: 10;weight: 1000;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 35),
(name: '& Small steel chest'                             ;   tval: 2; tchar: '&';flags:
  $0F000000;
    p1: 0;    cost: 200;  subval: 13; weight: 500;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d4'  ; level: 45),
(name: '& Large steel chest'                             ;   tval: 2; tchar: '&';flags:
  $23000000;
    p1: 0;    cost: 250;  subval: 16;weight: 1000;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ; level: 50),
(name: '& Rat Skeleton'                                  ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Giant Centipede Skeleton'                      ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 2;  weight: 25;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: 'Some filthy rags^ [%P6,%P4]'                     ;  tval: 36; tchar: '~';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 99;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: '& empty bottle'                                  ;   tval: 1; tchar: '!';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 4;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: 'Some shards of pottery'                          ;   tval: 1; tchar: '~';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 5;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& Human Skeleton'                                ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 7;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Dwarf Skeleton'                                ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 8;  weight: 60;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Elf Skeleton'                                  ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 9;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& Gnome Skeleton'                                ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 10;  weight: 25;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1),
(name: '& broken set of teeth'                           ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 11;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& large broken bone'                             ;   tval: 1; tchar: 's';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 12;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: '& broken stick'                                  ;   tval: 1; tchar: '~';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 13;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0)
				);


	{ Items which are sold in the stores are different from dungeon }
	{ items so that identify works properly.  Note that the players }
	{ recieve their initial items from this list, so position is    }
	{ very important...                                             }

	inventory_init :  
				  array [1..inven_init_max] of treasure_type = 	(
(name: '& Ration~ of Food'                               ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 5000;      cost: 3; subval: 307;  weight: 10;   number: 5;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 0), {  1}
(name: '& Hard Biscuit~'                                 ;  tval: 80; tchar: ',';flags:
  $00000000;
  p1: 500;      cost: 1; subval: 309;   weight: 2;   number: 5;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 0), {  2}
(name: '& Strip~ of Beef Jerky'                          ;  tval: 80; tchar: ',';flags:
  $00000000;
 p1: 1750;      cost: 2; subval: 310;   weight: 2;   number: 5;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '0d0'  ;  level: 0), {  3}
(name: '& Pint of Fine Ale'                              ;  tval: 80; tchar: ',';flags:
  $00000000;
  p1: 500;      cost: 1; subval: 311;  weight: 10;   number: 3;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 0), {  4}
(name: '& Pint of Fine Wine'                             ;  tval: 80; tchar: ',';flags:
  $00000000;
  p1: 400;      cost: 2; subval: 312;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '0d0'  ;  level: 0), {  5}
(name: '& Dagger (Misercorde) (%P2,%P3)'                 ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 2;  weight: 15;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0), {  6}
(name: '& Dagger (Stiletto) (%P2,%P3)'                   ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 10;   subval: 3;  weight: 12;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0), {  7}
(name: '& Bastard Sword (%P2,%P3)'                       ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 350;   subval: 7; weight: 140;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ;  level: 0), {  8}
(name: '& Broadsword (%P2,%P3)'                          ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 255;  subval: 10; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ;  level: 0), {  9}
(name: '& Longsword (%P2,%P3)'                           ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;    cost: 300;  subval: 18; weight: 130;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d10' ;  level: 0), { 10}
(name: '& Small Sword (%P2,%P3)'                         ;  tval: 23; tchar: '|';flags:
  $00000000;
    p1: 0;     cost: 48;  subval: 22;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 0), { 11}
(name: '& Broad Axe (%P2,%P3)'                           ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 304;   subval: 4; weight: 160;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ;  level: 0), { 12}
(name: '& Morningstar (%P2,%P3)'                         ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 396;   subval: 9; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;  level: 0), { 13}
(name: '& Mace (%P2,%P3)'                                ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 130;  subval: 10; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d4'  ;  level: 0), { 14}
(name: '& War Hammer (%P2,%P3)'                          ;  tval: 21; tchar: '\';flags:
  $00000000;
    p1: 0;    cost: 225;  subval: 11; weight: 120;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d3'  ;  level: 0), { 15}
(name: '& Halberd (%P2,%P3)'                             ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 430;   subval: 5; weight: 190;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '3d4'  ;  level: 0), { 16}
(name: '& Pike (%P2,%P3)'                                ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;    cost: 358;   subval: 7; weight: 160;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d5'  ;  level: 0), { 17}
(name: '& Spear (%P2,%P3)'                               ;  tval: 22; tchar: '/';flags:
  $00000000;
    p1: 0;     cost: 36;   subval: 8;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d6'  ;  level: 0), { 18}
(name: '& Short Bow (%P2)'                               ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 2;     cost: 50;   subval: 1;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 19}
(name: '& Long Bow (%P2)'                                ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 3;    cost: 120;   subval: 2;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 20}
(name: '& Light Crossbow (%P2)'                          ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 5;    cost: 160;  subval: 10; weight: 110;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 21}
(name: '& Sling (%P2)'                                   ;  tval: 20; tchar: '}';flags:
  $00000000;
    p1: 1;      cost: 5;  subval: 20;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 22}
(name: '& Arrow~ (%P2,%P3)'                              ;  tval: 12; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 1;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0), { 23}
(name: '& Bolt~ (%P2,%P3)'                               ;  tval: 11; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 2;   subval: 1;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d5'  ;  level: 0), { 24}
(name: '& Iron Shot~ (%P2,%P3)'                          ;  tval: 10; tchar: '{';flags:
  $00000000;
    p1: 0;      cost: 2;   subval: 1;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ;  level: 0), { 25}
(name: '& Pick (%P1) (%P2,%P3)'                          ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 1;     cost: 50;   subval: 1; weight: 150;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d3'  ;  level: 0), { 26}
(name: '& Shovel (%P1) (%P2,%P3)'                        ;  tval: 25; tchar: '\';flags:
  $20000000;
    p1: 0;     cost: 15;   subval: 2;  weight: 60;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 0), { 27}
(name: '& Pair of Soft Leather Boots [%P6,%P4]'          ;  tval: 30; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 7;   subval: 2;  weight: 30;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ;  level: 0), { 28}
(name: '& Pair of Hard Leather Boots [%P6,%P4]'          ;  tval: 30; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 12;   subval: 3;  weight: 40;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d1'  ;  level: 0), { 29}
(name: '& Hard Leather Cap [%P6,%P4]'                    ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 12;   subval: 2;  weight: 15;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '0d0'  ;  level: 0), { 30}
(name: '& Metal Cap [%P6,%P4]'                           ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 30;   subval: 3;  weight: 20;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d1'  ;  level: 0), { 31}
(name: '& Iron Helm [%P6,%P4]'                           ;  tval: 33; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 75;   subval: 4;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 5;
      toac: 0; damage: '1d3'  ;  level: 0), { 32}
(name: 'Soft Leather Armor [%P6,%P4]'                    ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 18;   subval: 2;  weight: 80;   number: 1;   tohit: 0;   todam: 0;   ac: 4;
      toac: 0; damage: '0d0'  ;  level: 0), { 33}
(name: 'Soft Studded Leather [%P6,%P4]'                  ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 35;   subval: 3;  weight: 90;   number: 1;   tohit: 0;   todam: 0;   ac: 5;
      toac: 0; damage: '1d1'  ;  level: 0), { 34}
(name: 'Hard Leather Armor [%P6,%P4]'                    ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;     cost: 55;   subval: 4; weight: 100;   number: 1;  tohit: -1;   todam: 0;   ac: 6;
      toac: 0; damage: '1d1'  ;  level: 0), { 35}
(name: 'Hard Studded Leather [%P6,%P4]'                  ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 100;   subval: 5; weight: 110;   number: 1;  tohit: -1;   todam: 0;   ac: 7;
      toac: 0; damage: '1d2'  ;  level: 0), { 36}
(name: 'Leather Scale Mail [%P6,%P4]'                    ;  tval: 36; tchar: '(';flags:
  $00000000;
    p1: 0;    cost: 330;   subval: 9; weight: 140;   number: 1;  tohit: -1;   todam: 0;  ac: 11;
      toac: 0; damage: '1d1'  ;  level: 0), { 37}
(name: 'Metal Scale Mail [%P6,%P4]'                      ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 430;   subval: 1; weight: 250;   number: 1;  tohit: -2;   todam: 0;  ac: 13;
      toac: 0; damage: '1d4'  ;  level: 0), { 38}
(name: 'Chain Mail [%P6,%P4]'                            ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 530;   subval: 2; weight: 220;   number: 1;  tohit: -2;   todam: 0;  ac: 14;
      toac: 0; damage: '1d4'  ;  level: 0), { 39}
(name: 'Partial Plate Armor [%P6,%P4]'                   ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;    cost: 900;   subval: 9; weight: 260;   number: 1;  tohit: -3;   todam: 0;  ac: 22;
      toac: 0; damage: '1d6'  ;  level: 0), { 40}
(name: 'Full Plate Armor [%P6,%P4]'                      ;  tval: 35; tchar: '[';flags:
  $00000000;
    p1: 0;   cost: 1050;  subval: 11; weight: 380;   number: 1;  tohit: -3;   todam: 0;  ac: 25;
      toac: 0; damage: '2d4'  ;  level: 0), { 41}
(name: '& Cloak [%P6,%P4]'                               ;  tval: 32; tchar: '(';flags:
  $00000000;
    p1: 0;      cost: 3;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 0), { 42}
(name: '& Set of Leather Gloves [%P6,%P4]'               ;  tval: 31; tchar: ']';flags:
  $00000000;
    p1: 0;      cost: 3;   subval: 1;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 1;
      toac: 0; damage: '0d0'  ;  level: 0), { 43}
(name: '& Set of Gauntlets [%P6,%P4]'                    ;  tval: 31; tchar: ']';flags:
  $00000000;
    p1: 0;     cost: 35;   subval: 2;  weight: 25;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ;  level: 0), { 44}
(name: '& Small Leather Shield [%P6,%P4]'                ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 30;   subval: 1;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 2;
      toac: 0; damage: '1d1'  ;  level: 0), { 45}
(name: '& Medium Leather Shield [%P6,%P4]'               ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 60;   subval: 2;  weight: 75;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d2'  ;  level: 0), { 46}
(name: '& Small Metal Shield [%P6,%P4]'                  ;  tval: 34; tchar: ')';flags:
  $00000000;
    p1: 0;     cost: 50;   subval: 4;  weight: 65;   number: 1;   tohit: 0;   todam: 0;   ac: 3;
      toac: 0; damage: '1d3'  ;  level: 0), { 47}
(name: '& Ring of Resist Fire'                           ;  tval: 45; tchar: '=';flags:
  $00080000;
    p1: 0;    cost: 250;  subval: 11;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 48}
(name: '& Ring of Resist Cold'                           ;  tval: 45; tchar: '=';flags:
  $00200000;
    p1: 0;    cost: 250;  subval: 12;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 49}
(name: '& Ring of Feather Falling'                       ;  tval: 45; tchar: '=';flags:
  $04000000;
    p1: 0;    cost: 250;  subval: 13;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 50}
(name: '& Ring of Protection [%P4]'                      ;  tval: 45; tchar: '=';flags:
  $00000000;
    p1: 0;    cost: 100;  subval: 24;   weight: 2;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 51}
(name: '& Amulet of Charisma (%P1)'                      ;  tval: 40; tchar: '"';flags:
  $00000020;
    p1: 0;    cost: 250;   subval: 6;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 52}
(name: '& Amulet of Slow Digestion'                      ;  tval: 40; tchar: '"';flags:
  $00000080;
    p1: 0;    cost: 200;   subval: 9;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 53}
(name: '& Amulet of Resist Acid'                         ;  tval: 40; tchar: '"';flags:
  $00100000;
    p1: 0;    cost: 300;  subval: 10;   weight: 3;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 54}
(name: '& Scroll~ of Enchant Weapon To-Hit'              ;  tval: 70; tchar: '?';flags:
  $00000001;
    p1: 0;    cost: 125; subval: 300;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 55}
(name: '& Scroll~ of Enchant Weapon To-Dam'              ;  tval: 70; tchar: '?';flags:
  $00000002;
    p1: 0;    cost: 125; subval: 301;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 56}
(name: '& Scroll~ of Enchant Armor'                      ;  tval: 70; tchar: '?';flags:
  $00000004;
    p1: 0;    cost: 125; subval: 302;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 57}
(name: '& Scroll~ of Identify'                           ;  tval: 70; tchar: '?';flags:
  $00000008;
    p1: 0;     cost: 50; subval: 303;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 58}
(name: '& Scroll~ of Remove Curse'                       ;  tval: 70; tchar: '?';flags:
  $00000010;
    p1: 0;    cost: 100; subval: 304;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 59}
(name: '& Scroll~ of Light'                              ;  tval: 70; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 305;   weight: 5;   number: 3;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 60}
(name: '& Scroll~ of Phase Door'                         ;  tval: 70; tchar: '?';flags:
  $00000080;
    p1: 0;     cost: 15; subval: 306;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 61}
(name: '& Scroll~ of Magic Mapping'                      ;  tval: 70; tchar: '?';flags:
  $00000800;
    p1: 0;     cost: 40; subval: 307;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 62}
(name: '& Scroll~ of Treasure Detection'                 ;  tval: 70; tchar: '?';flags:
  $00004000;
    p1: 0;     cost: 15; subval: 308;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 63}
(name: '& Scroll~ of Object Detection'                   ;  tval: 70; tchar: '?';flags:
  $00008000;
    p1: 0;     cost: 15; subval: 309;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 64}
(name: '& Scroll~ of Detect Invisible'                   ;  tval: 70; tchar: '?';flags:
  $00080000;
    p1: 0;     cost: 15; subval: 310;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 65}
(name: '& Scroll~ of Recharging'                         ;  tval: 70; tchar: '?';flags:
  $01000000;
    p1: 0;    cost: 200; subval: 311;   weight: 5;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 66}
(name: '& Book of Magic Spells [Beginners-Magik]'        ;  tval: 90; tchar: '?';flags:
  $0000007F;
    p1: 0;     cost: 25; subval: 257;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 67}
(name: '& Book of Magic Spells [Magik I]'                ;  tval: 90; tchar: '?';flags:
  $0000FF80;
    p1: 0;    cost: 100; subval: 258;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 68}
(name: '& Book of Magic Spells [Magik II]'               ;  tval: 90; tchar: '?';flags:
  $00FF0000;
    p1: 0;    cost: 400; subval: 259;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 69}
(name: '& Book of Magic Spells [The Mages Guide to Power]';  tval: 90; tchar: '?';flags:
  $7F000000;
    p1: 0;    cost: 800; subval: 261;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 70}
(name: '& Holy Book of Prayers [Beginners Handbook]'     ;  tval: 91; tchar: '?';flags:
  $000000FF;
    p1: 0;     cost: 25; subval: 258;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 71}
(name: '& Holy Book of Prayers [Words of Wisdom]'        ;  tval: 91; tchar: '?';flags:
  $0000FF00;
    p1: 0;    cost: 100; subval: 259;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 72}
(name: '& Holy Book of Prayers [Chants and Blessings]'   ;  tval: 91; tchar: '?';flags:
  $01FF0000;
    p1: 0;    cost: 300; subval: 260;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 73}
(name: '& Holy Book of Prayers [Exorcism and Dispelling]';  tval: 91; tchar: '?';flags:
  $7E000000;
    p1: 0;    cost: 900; subval: 261;  weight: 30;   number: 1;tohit: -100;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 74}
(name: '& Potion~ of Restore Strength'                   ;  tval: 75; tchar: '!';flags:
  $00000004;
    p1: 0;    cost: 300; subval: 310;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 75}
(name: '& Potion~ of Restore Intelligence'               ;  tval: 75; tchar: '!';flags:
  $00000020;
    p1: 0;    cost: 300; subval: 311;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 76}
(name: '& Potion~ of Restore Wisdom'                     ;  tval: 75; tchar: '!';flags:
  $00000100;
    p1: 0;    cost: 300; subval: 312;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 77}
(name: '& Potion~ of Restore Charisma'                   ;  tval: 75; tchar: '!';flags:
  $00000800;
    p1: 0;    cost: 300; subval: 313;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 78}
(name: '& Potion~ of Cure Light Wounds'                  ;  tval: 75; tchar: '!';flags:
  $10001000;
   p1: 50;     cost: 15; subval: 314;   weight: 4;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d1'  ;  level: 0), { 79}
(name: '& Potion~ of Cure Serious Wounds'                ;  tval: 75; tchar: '!';flags:
  $30002000;
  p1: 100;     cost: 40; subval: 315;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0), { 80}
(name: '& Potion~ of Cure Critical Wounds'               ;  tval: 75; tchar: '!';flags:
  $70004000;
  p1: 100;    cost: 100; subval: 316;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
    toac: 0; damage: '1d1'  ;  level: 0), { 81}
(name: '& Potion~ of Restore Dexterity'                  ;  tval: 75; tchar: '!';flags:
  $04000000;
    p1: 0;    cost: 300; subval: 317;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 82}
(name: '& Potion~ of Restore Constitution'               ;  tval: 75; tchar: '!';flags:
  $68000000;
    p1: 0;    cost: 300; subval: 318;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 83}
(name: '& Potion~ of Heroism'                            ;  tval: 76; tchar: '!';flags:
  $00000010;
    p1: 0;     cost: 35; subval: 319;   weight: 4;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 84}
(name: '& Potion~ of Boldliness'                         ;  tval: 76; tchar: '!';flags:
  $00000040;
    p1: 0;     cost: 10; subval: 320;   weight: 4;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 85}
(name: '& Wand of Light (%P1 charges)'                   ;  tval: 65; tchar: '-';flags:
  $00000001;
    p1: 0;    cost: 200;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2), { 86}
(name: '& Wand of Lightning Bolts (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00000002;
    p1: 0;    cost: 600;   subval: 2;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 6), { 87}
(name: '& Wand of Magic Missile (%P1 charges)'            ;  tval: 65; tchar: '-';flags:
  $00002000;
    p1: 0;    cost: 200;  subval: 14;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 2), { 88}
(name: '& Wand of Disarming (%P1 charges)'               ;  tval: 65; tchar: '-';flags:
  $00020000;
    p1: 0;    cost: 700;  subval: 18;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 12), { 89}
(name: '& Wand of Lightning Balls (%P1 charges)'         ;  tval: 65; tchar: '-';flags:
  $00040000;
    p1: 0;   cost: 1200;  subval: 19;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 20), { 90}
(name: '& Wand of Wonder (%P1 charges)'                  ;  tval: 65; tchar: '-';flags:
  $00800000;
    p1: 0;    cost: 250;  subval: 24;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ; level: 10), { 91}
(name: '& Staff of Light (%P1 charges)'                  ;  tval: 55; tchar: '_';flags:
  $00000001;
    p1: 0;    cost: 250;   subval: 1;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 3), { 92}
(name: '& Staff of Door/Stair Location (%P1 charges)'    ;  tval: 55; tchar: '_';flags:
  $00000002;
    p1: 0;    cost: 350;   subval: 2;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 7), { 93}
(name: '& Staff of Trap Location (%P1 charges)'          ;  tval: 55; tchar: '_';flags:
  $00000004;
    p1: 0;    cost: 350;   subval: 3;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 7), { 94}
(name: '& Staff of Detect Invisible (%P1 charges)'       ;  tval: 55; tchar: '_';flags:
  $00008000;
    p1: 0;    cost: 200;  subval: 16;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d2'  ;  level: 3), { 95}
(name: '& Potion~ of Restore Life Levels'                ;  tval: 76; tchar: '!';flags:
  $00000080;
    p1: 0;    cost: 400; subval: 321;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 96}
(name: '& Scroll~ of Blessing'                           ;  tval: 71; tchar: '?';flags:
  $00000020;
    p1: 0;     cost: 15; subval: 312;   weight: 5;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 97}
(name: '& Scroll~ of Word-of-Recall'                     ;  tval: 71; tchar: '?';flags:
  $00000100;
    p1: 0;    cost: 150; subval: 313;   weight: 5;   number: 3;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0), { 98}
(name: '& Potion~ of Slow Poison'                        ;  tval: 76; tchar: '!';flags:
  $00000800;
    p1: 0;     cost: 25; subval: 322;   weight: 4;   number: 2;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), { 99}
(name: '& Potion~ of Neutralize Poison'                  ;  tval: 76; tchar: '!';flags:
  $00001000;
    p1: 0;     cost: 75; subval: 323;   weight: 4;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0), {100}
(name: '& Wand of Stinking Cloud (%P1 charges)'          ;  tval: 65; tchar: '-';flags:
  $00200000;
    p1: 0;    cost: 400;  subval: 22;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 5), {101}
(name: '& Iron Spike~'                                   ;  tval: 13; tchar: '~';flags:
  $00000000;
    p1: 0;      cost: 1;   subval: 1;  weight: 10;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 1), {102}
(name: '& Brass Lantern~ with %P5 turns of light'        ;  tval: 15; tchar: '~';flags:
  $00000000;
 p1: 7500;     cost: 35;   subval: 2;  weight: 50;   number: 1;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '1d1'  ;  level: 1), {103}
(name: '& Wooden Torch~ with %P5 turns of light'         ;  tval: 15; tchar: '~';flags:
  $00000000;
 p1: 4000;      cost: 2; subval: 270;  weight: 30;   number: 5;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '1d1'  ;  level: 1), {104}
(name: '& Flask~ of oil'                                 ;  tval: 77; tchar: '!';flags:
  $00040000;
 p1: 7500;      cost: 3; subval: 257;  weight: 10;   number: 5;   tohit: 0;   todam: 0;   ac: 0;
   toac: 0; damage: '2d6'  ;  level: 1)  {105}
					);

	store_choice	:  
				  array [1..max_stores] of 
				  array [1..store$choices] of integer = 	(
	{ General Store }
(105,104,103,102,102,104,42,105,104,27,26,5,4,3,3,2,2,2,1,1,1,1,1,1,1,1
),
	{ Armory        }
(30,31,32,33,34,35,36,37,38,39,40,41,43,44,45,46,47,30,33,34,43,44,28,29,30,31
),
	{ Weaponsmith   }
( 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25, 6, 7,23,25,23,25
),
	{ Temple        }
(71,72,73,74,59,59,77,79,80,81,84,85,13,14,15,96,97,98,100,79,79,80,80,81,72,98
),
	{ Alchemy shop  }
(55,56,57,58,58,60,61,62,63,64,65,66,75,76,78,82,83,60,61,62,63,64,98,99,98,98
),
	{ Magic-User store}
(67,49,50,51,52,53,54,48,68,69,69,70,86,87,88,89,90,91,92,93,94,95,86,101,68,88
)
				);

	{ Each store will buy only certain items, based on TVAL }
	store_buy       :  
				  array [1..max_stores] of obj_set =       (
				[25,30,32,80,77,15,13],
				[30,31,33,34,35,36],
				[10,11,12,20,21,22,23],
				[21,70,71,75,76,91],
				[70,71,75,76],
				[40,45,55,65,70,71,75,76,90]
				);

	{ Store owners have different characteristics for pricing and haggling}
	{ Note: Store owners should be added in groups, one for each store    }
	owners          :  
				  array [1..max_owners] of owner_type =       (
(owner_name: 'Erick the Honest       (Human)      General Store';
	  max_cost: 250; max_inflate: 0.75; min_inflate: 0.08; haggle_per: 0.04; owner_race: 1;
	    insult_max: 12),
(owner_name: 'Mauglin the Grumpy     (Dwarf)      Armory'       ;
	max_cost: 32000; max_inflate: 1.00; min_inflate: 0.12; haggle_per: 0.04; owner_race: 6;
	  insult_max: 5),
(owner_name: 'Arndal Beast-Slayer    (Half-Elf)   Weaponsmith'  ;
	max_cost: 10000; max_inflate: 0.85; min_inflate: 0.10; haggle_per: 0.05; owner_race: 2;
	  insult_max: 8),
(owner_name: 'Hardblow the Humble    (Human)      Temple'       ;
	 max_cost: 3500; max_inflate: 0.75; min_inflate: 0.09; haggle_per: 0.06; owner_race: 1;
	   insult_max: 15),
(owner_name: 'Ga-nat the Greedy      (Gnome)      Alchemist'    ;
	max_cost: 12000; max_inflate: 1.20; min_inflate: 0.15; haggle_per: 0.04; owner_race: 5;
	  insult_max: 9),
(owner_name: 'Valeria Starshine      (Elf)        Magic Shop'   ;
	max_cost: 32000; max_inflate: 0.75; min_inflate: 0.10; haggle_per: 0.05; owner_race: 3;
	  insult_max: 11),
(owner_name: 'Andy the Friendly      (Halfling)   General Store';
	  max_cost: 200; max_inflate: 0.70; min_inflate: 0.08; haggle_per: 0.05; owner_race: 4;
	    insult_max: 15),
(owner_name: 'Darg-Low the Grim      (Human)      Armory'       ;
	max_cost: 10000; max_inflate: 0.90; min_inflate: 0.11; haggle_per: 0.04; owner_race: 1;
	  insult_max: 9),
(owner_name: 'Oglign Dragon-Slayer   (Dwarf)      Weaponsmith'  ;
	max_cost: 32000; max_inflate: 0.95; min_inflate: 0.12; haggle_per: 0.04; owner_race: 6;
	  insult_max: 8),
(owner_name: 'Gunnar the Paladin     (Human)      Temple'       ;
	 max_cost: 5000; max_inflate: 0.85; min_inflate: 0.10; haggle_per: 0.05; owner_race: 1;
	   insult_max: 23),
(owner_name: 'Mauser the Chemist     (Half-Elf)   Alchemist'    ;
	max_cost: 10000; max_inflate: 0.90; min_inflate: 0.11; haggle_per: 0.05; owner_race: 2;
	  insult_max: 8),
(owner_name: 'Gopher the Great!      (Gnome)      Magic Shop'   ;
	max_cost: 20000; max_inflate: 1.15; min_inflate: 0.13; haggle_per: 0.06; owner_race: 5;
	  insult_max: 10),
(owner_name: 'Lyar-el the Comely     (Elf)        General Store';
	  max_cost: 300; max_inflate: 0.65; min_inflate: 0.07; haggle_per: 0.06; owner_race: 3;
	    insult_max: 18),
(owner_name: 'Mauglim the Horrible   (Half-Orc)   Armory'       ;
	 max_cost: 3000; max_inflate: 1.00; min_inflate: 0.13; haggle_per: 0.05; owner_race: 7;
	   insult_max: 9),
(owner_name: 'Ithyl-Mak the Beastly  (Half-Troll) Weaponsmith'  ;
	 max_cost: 3000; max_inflate: 1.10; min_inflate: 0.15; haggle_per: 0.06; owner_race: 8;
	   insult_max: 8),
(owner_name: 'Delihla the Pure       (Half-Elf)   Temple'       ;
	max_cost: 25000; max_inflate: 0.80; min_inflate: 0.07; haggle_per: 0.06; owner_race: 2;
	  insult_max: 20),
(owner_name: 'Wizzle the Chaotic     (Halfling)   Alchemist'    ;
	max_cost: 10000; max_inflate: 0.90; min_inflate: 0.10; haggle_per: 0.06; owner_race: 4;
	  insult_max: 8),
(owner_name: 'Inglorian the Mage     (Human?)     Magic Shop'   ;
	max_cost: 32000; max_inflate: 1.00; min_inflate: 0.10; haggle_per: 0.07; owner_race: 1;
	  insult_max: 10)
				);

	{ Each type of character starts out with a few provisions...	}
	{ Note the the entries refer to array elements of INVENTORY_INIT array}
	player_init     :  
				  array [1..max_class] of
				  array [1..5] of byteint =       (
		(   1, 104,  42,   7,  33),     { Warrior       }
		(   1, 104,  42,   7,  67),     { Mage          }
		(   1, 104,  42,   7,  71),     { Priest        }
		(   1, 104,   7,  33,  67),     { Rogue         }
		(   1, 104,  42,   7,  67),     { Ranger        }
		(   1, 104,  42,   7,  71)      { Paladin       }
				);


	{ Identified objects flags					}
	object_ident :  
				  array [1..max_objects] of boolean =  (max_objects of false);

	{ Traps are just Nasty treasures...				}
	trap_lista      :  
				  array [1..max_trapa]   of treasure_type =       (
(name: 'an open pit'                                     ; tval: 102; tchar: ' ';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;level: -50),
(name: 'an arrow trap'                                   ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 2;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ;  level: 0),
(name: 'a covered pit'                                   ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 3;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;  level: 0),
(name: 'a trap door'                                     ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 4;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d8'  ;  level: 0),
(name: 'a gas trap'                                      ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 5;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0),
(name: 'a loose rock'                                    ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 6;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'a dart trap'                                     ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 7;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0),
(name: 'a strange rune'                                  ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 8;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'some loose rock'                                 ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 9;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;  level: 0),
(name: 'a gas trap'                                      ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 10;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 0),
(name: 'a strange rune'                                  ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 11;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'a blackened spot'                                ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 12;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d6'  ;  level: 0),
(name: 'some corroded rock'                              ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 13;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '4d6'  ;  level: 0),
(name: 'a gas trap'                                      ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 14;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;  level: 0),
(name: 'a gas trap'                                      ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 15;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ; level: 10),
(name: 'a gas trap'                                      ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 16;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ;  level: 5),
(name: 'a dart trap'                                     ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 17;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ; level: 10),
(name: 'a dart trap'                                     ; tval: 101; tchar: '.';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 18;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ; level: 10)
				);

	{ Traps: Level represents the difficulty of disarming;	}
	{ and P1 represents the experienced gained when disarmed}
	trap_listb      :  
				  array [1..max_trapb]   of treasure_type =       (
(name: 'an open pit'                                     ; tval: 102; tchar: ' ';flags:
  $00000000;
    p1: 1;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;level: -50),
(name: 'an arrow trap'                                   ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 3;      cost: 0;   subval: 2;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ;level: -10),
(name: 'a covered pit'                                   ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 2;      cost: 0;   subval: 3;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;level: -40),
(name: 'a trap door'                                     ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;   subval: 4;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d8'  ;level: -25),
(name: 'a gas trap'                                      ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 3;      cost: 0;   subval: 5;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ;  level: 5),
(name: 'a loose rock'                                    ; tval: 102; tchar: ';';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 6;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;level: -90),
(name: 'a dart trap'                                     ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;   subval: 7;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ; level: 10),
(name: 'a strange rune'                                  ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;   subval: 8;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;level: -10),
(name: 'some loose rock'                                 ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;   subval: 9;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;level: -10),
(name: 'a gas trap'                                      ; tval: 102; tchar: '^';flags:
  $00000000;
   p1: 10;      cost: 0;  subval: 10;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '1d4'  ;  level: 5),
(name: 'a strange rune'                                  ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 11;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;level: -10),
(name: 'a blackened spot'                                ; tval: 102; tchar: '^';flags:
  $00000000;
   p1: 10;      cost: 0;  subval: 12;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '4d6'  ; level: 10),
(name: 'some corroded rock'                              ; tval: 102; tchar: '^';flags:
  $00000000;
   p1: 10;      cost: 0;  subval: 13;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
     toac: 0; damage: '4d6'  ; level: 10),
(name: 'a gas trap'                                      ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 14;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '2d6'  ;  level: 5),
(name: 'a gas trap'                                      ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 15;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d4'  ; level: 10),
(name: 'a gas trap'                                      ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 16;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ;  level: 5),
(name: 'a dart trap'                                     ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 17;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ; level: 10),
(name: 'a dart trap'                                     ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 5;      cost: 0;  subval: 18;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d8'  ; level: 10),
	{ Special case, see DOOR_LIST below (subvals must agree)        }
(name: 'a closed door'                                   ; tval: 105; tchar: '+';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 19;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0)
				);

	{ Stores are just special traps 		}
	store_door      :  
				  array [1..max_stores] of treasure_type =  (
(name: 'The entrance to the General Store.'              ; tval: 110; tchar: '1';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 101;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'The entrance to the Armory.'                     ; tval: 110; tchar: '2';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 102;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'The entrance to the Weapon Smiths.'              ; tval: 110; tchar: '3';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 103;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'The entrance to the Temple.'                     ; tval: 110; tchar: '4';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 104;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'The entrance to the Alchemy Shop.'               ; tval: 110; tchar: '5';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 105;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0),
(name: 'The entrance to the Magic Shop.'                 ; tval: 110; tchar: '6';flags:
  $00000000;
    p1: 0;      cost: 0; subval: 106;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0)
				);


 scare_monster :  
				  treasure_type = 
(name: 'a strange rune'                                  ; tval: 102; tchar: '^';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 99;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;level: -90);

 rubble :  
				  treasure_type = 
(name: 'some rubble'                                     ; tval: 103; tchar: ':';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '0d0'  ;  level: 0);


	{ Secret door must have same subval as closed door in	}
	{ TRAP_LISTB.  See CHANGE_TRAP                          }
	door_list       :  
				  array [1..3]		 of treasure_type =       (
(name: 'an open door'                                    ; tval: 104;tchar: '''';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: 'a closed door'                                   ; tval: 105; tchar: '+';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 19;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0),
(name: 'a secret door'                                   ; tval: 109; tchar: '#';flags:
  $00000000;
    p1: 0;      cost: 0;  subval: 19;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0)
				);

 up_stair   :  
				  treasure_type = 
(name: 'an up staircase '                                ; tval: 107; tchar: '<';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0);

 down_stair :  
				  treasure_type = 
(name: 'a down staircase'                                ; tval: 108; tchar: '>';flags:
  $00000000;
    p1: 0;      cost: 0;   subval: 1;   weight: 0;   number: 0;   tohit: 0;   todam: 0;   ac: 0;
      toac: 0; damage: '1d1'  ;  level: 0);


	{ Sets for easy testing 					}
	floor_set   :  obj_set =  [1,2,4,5,6,7];
	wall_set    :  obj_set =  [10,11,12];
	pwall_set   :  obj_set =  [10,11,12,15];
	corr_set    :  obj_set =  [4,5];
	trap_set    :  obj_set =  [101,102,109,110];
	light_set   :  obj_set =  [102,103,104,105,107,108,109,110];

	{ Descriptive phrases						}
	colors  :  
				  array [1..max_colors]	 of atype =    ('Amber','Azure','Blue','Blue Speckled','Blue Spotted',
		      'Black','Black Speckled','Black Spotted',
		      'Brown','Brown Speckled','Brown Spotted',
		      'Bubbling',
		      'Chartreuse','Clear','Cloudy',
		      'Copper','Copper Spotted','Crimson','Cyan',
		      'Dark Blue','Dark Green','Dark Red','Ecru',
		      'Gold','Gold Spotted',
		      'Green','Green Speckled','Green Spotted',
		      'Grey','Grey Spotted','Hazy','Indigo',
		      'Light Blue','Light Green','Magenta','Metallic Blue',
		      'Metallic Red','Metallic Green','Metallic Purple',
		      'Misty',
		      'Orange','Orange Speckled','Orange Spotted',
		      'Pink','Pink Speckled',
		      'Plaid','Puce','Purple','Purple Speckled',
		      'Purple Spotted','Red','Red Speckled','Red Spotted',
		      'Silver','Silver Speckled','Silver Spotted','Smokey',
		      'Tan','Tangerine','Topaz','Turquoise',
		      'Violet','Vermilion','White','White Speckled',
		      'White Spotted','Yellow'
		     );
	mushrooms:  
				  array [1..max_mush]    of atype =    ('Blue','Black','Brown','Copper','Crimson',
		      'Dark blue','Dark green','Dark red','Gold',
		      'Green','Grey','Light Blue','Light Green',
		      'Orange','Pink','Plaid','Purple','Red','Tan',
		      'Turquoise','Violet','White','Yellow',
		      'Wrinkled','Wooden','Slimey','Speckled',
		      'Spotted','Furry'
		     );
	woods   :  
				  array [1..max_woods]   of atype =    ('Applewood','Ashen','Aspen','Avocado wood',
		      'Balsa','Banyan','Birch','Cedar','Cherrywood',
		      'Cinnibar','Cottonwood','Cypress','Dogwood',
		      'Driftwood','Ebony','Elm wood','Eucalyptus',
		      'Grapevine','Hawthorn','Hemlock','Hickory',
		      'Iron wood','Juniper','Locust','Mahogany',
		      'Magnolia','Manzanita','Maple','Mulberry',
		      'Oak','Pecan','Persimmon','Pine','Redwood',
		      'Rosewood','Spruce','Sumac','Sycamore','Teak',
		      'Walnut','Zebra wood'
		     );
	metals  :  
				  array [1..max_metals]  of atype =    ('Aluminium','Bone','Brass','Bronze','Cast Iron',
		      'Chromium','Copper','Gold','Iron','Lead',
		      'Magnesium','Molybdenum','Nickel',
		      'Pewter','Rusty','Silver','Steel','Tin',
		      'Titanium','Tungsten','Zirconium','Zinc',
		      'Aluminium Plated','Brass Plated','Copper Plated',
		      'Gold Plated','Nickel Plated','Silver Plated',
		      'Steel Plated','Tin Plated','Zinc Plated'
		     );
	rocks   :  
				  array [1..max_rocks]   of atype =    ('Amber','Agate','Alexandrite','Amethyst','Antlerite',
		      'Aquamarine','Argentite','Azurite','Beryl','Bloodstone',
		      'Calcite','Carnelian','Coral','Corundum','Cryolite',
		      'Diamond','Diorite','Emerald','Flint','Fluorite',
		      'Gabbro','Garnet','Granite','Gypsum','Hematite','Jade',
		      'Jasper','Kryptonite','Lapus lazuli','Limestone',
		      'Malachite','Manganite','Marble','Moonstone',
		      'Neptunite','Obsidian','Onyx','Opal','Pearl','Pyrite',
		      'Quartz','Quartzite','Rhodonite','Rhyolite','Ruby',
		      'Saphire','Sphalerite','Staurolite','Tiger eye','Topaz',
		      'Turquoise','Zircon'
		     );
	amulets :  
				  array [1..max_amulets] of atype =    ('Birch','Cedar','Dogwood','Driftwood',
		      'Elm wood','Hemlock','Hickory','Mahogany',
		      'Maple','Oak','Pine','Redwood','Rosewood',
		      'Walnut','Aluminium','Bone','Brass','Bronze',
		      'Copper','Iron','Lead','Nickel','Agate','Amethyst',
		      'Diamond','Emerald','Flint','Garnet',
		      'Jade','Obsidian','Onyx','Opal','Pearl','Quartz',
		      'Ruby','Saphire','Tiger eye','Topaz','Turquoise'
		     );
	syllables :  
				  array [1..max_syllables] of dtype =  ('a','ab','ag','aks','ala','an','ankh','app',
		      'arg','arze','ash','aus','ban','bar','bat','bek',
		      'bie','bin','bit','bjor','blu','bot','bu',
		      'byt','comp','con','cos','cre','dalf','dan',
		      'den','doe','dok','eep','el','eng','er','ere','erk',
		      'esh','evs','fa','fid','for','fri','fu','gan',
		      'gar','glen','gop','gre','ha','he','hyd','i',
		      'ing','ion','ip','ish','it','ite','iv','jo',
		      'kho','kli','klis','la','lech','man','mar',
		      'me','mi','mic','mik','mon','mung','mur','nej',
		      'nelg','nep','ner','nes','nis','nih','nin','o',
		      'od','ood','org','orn','ox','oxy','pay','pet',
		      'ple','plu','po','pot','prok','re','rea','rhov',
		      'ri','ro','rog','rok','rol','sa','san','sat',
		      'see','sef','seh','shu','ski','sna','sne','snik',
		      'sno','so','sol','sri','sta','sun','ta','tab',
		      'tem','ther','ti','tox','trol','tue','turs','u',
		      'ulk','um','un','uni','ur','val','viv','vly',
		      'vom','wah','wed','werg','wex','whon','wun','x',
		      'yerg','yp','zun'
		     );

	{ Used in DESC.INC for replacing the & in descriptions		}
	vowel_set       :  
				  char_set =  ['a','e','i','o','u','A','E','I','O','U'];

	{ Creatures must be defined here				}
	{       See TYPES.INC under creature_type for a complete list
		of all variables for creatures.  Some of the less obvious
		are explained below.

	Hit points:	'#1d#2' where #2 is the range of each roll and
			#1 is the number of added up rolls to make.
			Example: a creature with 5 eight-sided hit die
			is given '5d8'.

		Attack types:
		1       Normal attack
		2       Poison Strength
		3       Confusion attack
		4       Fear attack
		5       Fire attack
		6       Acid attack
		7       Cold attack
		8       Lightning attack
		9       Corrosion attack
		10      Blindness attack
		11      Paralysis attack
		12      Steal Money
		13      Steal Object
		14      Poison
		15      Lose dexterity
		16      Lose constitution
		17      Lose intelligence
		18      Lose wisdom
		19      Lose experience
		20      Aggravation
		21      Disenchants
		22      Eats food
		23      Eats light
		24      Eats charges
		99      Blank

		Attack descriptions:
		1       hits you.
		2       bites you.
		3       claws you.
		4       stings you.
		5       touches you.
		6       kicks you.
		7       gazes at you.
		8       breathes on you.
		9       spits on you.
		10      makes a horrible wail.
		11      embraces you.
		12      crawls on you.
		13      releases a cloud of spores.
		14      begs you for money.
		15      You've been slimed.
		16      crushes you.
		17      tramples you.
		18      drools on you.
		19      insults you.
		99      is repelled.

	Example:  For a creature which bites for 1d6, then stings for
		  2d4 and loss of dex you would use:
			'1 2 1d6|15 4 2d4'

		CMOVE flags:
Movement.       00000001        Move only to attack
	.       00000002        Move, attack normal
	.       00000008        20% random movement
	.       00000010        40% random movement
	.       00000020        75% random movement
Special +       00010000        Invisible movement
	+       00020000        Move through door
	+       00040000        Move through wall
	+       00080000        Move through creatures
	+       00100000        Picks up objects
	+       00200000        Multiply monster
Carries =       01000000        Carries objects.
	=       02000000        Carries gold.
	=       04000000        Has 60% of time.
	=       08000000        Has 90% of time.
	=       10000000        1d2 objects/gold.
	=       20000000        2d2 objects/gold.
	=       40000000        4d2 objects/gold.
Special ~       80000000        Win-the-Game creature.

		SPELL Flags:
Frequency       000001    1     These add up to x.  Then
(1 in x).       000002    2     if RANDINT(X) = 1 the
	.       000004    4     creature casts a spell.
	.       000008    8
Spells  =       000010  Teleport short (blink)
	=       000020  Teleport long
	=       000040  Teleport player to monster
	=       000080  Cause light wound
	=       000100  Cause serious wound
	=       000200  Hold person (Paralysis)
	=       000400  Cause blindness
	=       000800  Cause confusion
	=       001000  Cause fear
	=       002000  Summon monster
	=       004000  Summon undead
	=       008000  Slow Person
	=       010000  Drain Mana
	=       020000  Not Used
	=       040000  Not Used
Breaths +       080000  Breath Lightning
	+       100000  Breath Gas
	+       200000  Breath Acid
	+       400000  Breath Frost
	+       800000  Breath Fire

		CDEFENSE flags:
		0001    Hurt by Slay Dragon.
		0002    Hurt by Slay Monster.
		0004    Hurt by Slay Evil.
		0008    Hurt by Slay Undead.
		0010    Hurt by Frost.
		0020    Hurt by Fire.
		0040    Hurt by Poison.
		0080    Hurt by Acid.
		0100    Hurt by Light-Wand.
		0200    Hurt by Stone-to-Mud.
		0400    Not used.
		0800    Not used.
		1000    Cannot be charmed or slept.
		2000    Can be seen with infra-vision.
		4000    Max Hit points.
		8000    Not used.


	Sleep (sleep)	:	A measure in turns of how fast creature
				will notice player (on the average).
	Area of affect (aaf) :  Max range that creature is able to "notice"
				the player.
									}
	c_list  :  
			  array [1..max_creatures] of creature_type =               (
(name: 'Filthy Street Urchin'     ;cmove: $0012000A;spells: $00000000;cdefense: $2034;
  sleep: 400;    mexp: 0;
   aaf: 4;   ac: 1; speed: 1; cchar: 'p'; hd: '1d4'   ; damage: '1 14 0d0|12 5 0d0'              ;
     level: 0),
(name: 'Blubbering Idiot'         ;cmove: $0012000A;spells: $00000000;cdefense: $2030;
  sleep: 000;    mexp: 0;
   aaf: 6;   ac: 1; speed: 1; cchar: 'p'; hd: '1d2'   ; damage: '1 18 0d0'                       ;
     level: 0),
(name: 'Pitiful Looking Beggar'   ;cmove: $0012000A;spells: $00000000;cdefense: $2030;
  sleep: 400;    mexp: 0;
  aaf: 10;   ac: 1; speed: 1; cchar: 'p'; hd: '1d4'   ; damage: '1 14 0d0'                       ;
    level: 0),
(name: 'Mangy Looking Leper'      ;cmove: $0012000A;spells: $00000000;cdefense: $2030;
  sleep: 500;    mexp: 0;
  aaf: 10;   ac: 1; speed: 1; cchar: 'p'; hd: '1d1'   ; damage: '1 14 0d0'                       ;
    level: 0),
(name: 'Squint Eyed Rogue'        ;cmove: $07120002;spells: $00000000;cdefense: $2034;
  sleep: 999;    mexp: 0;
  aaf: 10;   ac: 8; speed: 1; cchar: 'p'; hd: '2d8'   ; damage: '1 1 1d6|13 5 0d0'               ;
    level: 0),
(name: 'Singing, Happy Drunk'     ;cmove: $06120038;spells: $00000000;cdefense: $2030;
  sleep: 0;    mexp: 0;
  aaf: 10;   ac: 1; speed: 1; cchar: 'p'; hd: '2d3'   ; damage: '1 14 0d0'                       ;
    level: 0),
(name: 'Mean Looking Mercenary'   ;cmove: $0B12000A;spells: $00000000;cdefense: $2034;
  sleep: 25000;    mexp: 0;
  aaf: 10;  ac: 20; speed: 1; cchar: 'p'; hd: '5d8'   ; damage: '1 1 1d10'                       ;
    level: 0),
(name: 'Battle Scarred Veteran'   ;cmove: $0B12000A;spells: $00000000;cdefense: $2030;
  sleep: 25000;    mexp: 0;
  aaf: 10;  ac: 30; speed: 1; cchar: 'p'; hd: '7d8'   ; damage: '1 1 2d6'                        ;
    level: 0),
(name: 'Grey Mushroom patch'      ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 1;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '1d2'   ; damage: '3 13 1d4'                       ;
     level: 1),
(name: 'Giant Yellow Centipede'   ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 300;    mexp: 2;
   aaf: 8;  ac: 12; speed: 1; cchar: 'c'; hd: '2d6'   ; damage: '1 2 1d3|1 4 1d3'                ;
     level: 1),
(name: 'Giant White Centipede'    ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 400;    mexp: 2;
   aaf: 7;  ac: 10; speed: 1; cchar: 'c'; hd: '3d5'   ; damage: '1 2 1d2|1 4 1d2'                ;
     level: 1),
(name: 'White Icky-Thing'         ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 100;    mexp: 2;
  aaf: 12;   ac: 7; speed: 1; cchar: 'i'; hd: '3d5'   ; damage: '1 5 1d2'                        ;
    level: 1),
(name: 'Clear Icky-Thing'         ;cmove: $00010002;spells: $00000000;cdefense: $0022;
  sleep: 100;    mexp: 1;
  aaf: 12;   ac: 6; speed: 1; cchar: 'i'; hd: '2d5'   ; damage: '1 5 1d2'                        ;
    level: 1),
(name: 'Giant White Mouse'        ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 200;    mexp: 1;
   aaf: 8;   ac: 4; speed: 1; cchar: 'r'; hd: '1d3'   ; damage: '1 2 1d2'                        ;
     level: 1),
(name: 'Large Brown Snake'        ;cmove: $0000000A;spells: $00000000;cdefense: $00B0;
  sleep: 999;    mexp: 3;
   aaf: 4;  ac: 35; speed: 0; cchar: 'R'; hd: '4d6'   ; damage: '1 2 1d3|1 16 1d4'               ;
     level: 1),
(name: 'Large White Snake'        ;cmove: $00000012;spells: $00000000;cdefense: $00B0;
  sleep: 999;    mexp: 2;
   aaf: 4;  ac: 30; speed: 1; cchar: 'R'; hd: '3d6'   ; damage: '1 2 1d1'                        ;
     level: 1),
(name: 'Kobold'                   ;cmove: $07020002;spells: $00000000;cdefense: $2032;
  sleep: 100;    mexp: 5;
  aaf: 20;  ac: 16; speed: 1; cchar: 'k'; hd: '3d7'   ; damage: '1 1 1d6'                        ;
    level: 1),
(name: 'White Worm mass'          ;cmove: $00200022;spells: $00000000;cdefense: $01B0;
  sleep: 1;    mexp: 2;
   aaf: 6;   ac: 1; speed: 0; cchar: 'w'; hd: '4d4'   ; damage: '14 12 1d2'                      ;
     level: 1),
(name: 'Floating Eye'             ;cmove: $00000001;spells: $0001000D;cdefense: $2102;
  sleep: 100;    mexp: 1;
   aaf: 2;   ac: 6; speed: 1; cchar: 'e'; hd: '3d6'   ; damage: '11 7 0d0'                       ;
     level: 1),
(name: 'Shrieker Mushroom patch'  ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 1;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '1d1'   ; damage: '20 10 0d0'                      ;
     level: 2),
(name: 'Blubbering Icky-Thing'    ;cmove: $0B180012;spells: $00000000;cdefense: $0022;
  sleep: 100;    mexp: 8;
  aaf: 10;   ac: 4; speed: 1; cchar: 'i'; hd: '5d8'   ; damage: '14 12 1d4|22 12 0d0'            ;
    level: 2),
(name: 'Metallic Green Centipedes';cmove: $00000012;spells: $00000000;cdefense: $0000;
  sleep: 100;    mexp: 3;
   aaf: 5;   ac: 4; speed: 2; cchar: 'c'; hd: '4d4'   ; damage: '1 12 1d1'                       ;
     level: 2),
(name: 'Novice Warrior'           ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 50;    mexp: 6;
  aaf: 20;  ac: 16; speed: 1; cchar: 'p'; hd: '9d4'   ; damage: '1 1 1d7'                        ;
    level: 2),
(name: 'Novice Rogue'             ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 50;    mexp: 6;
  aaf: 20;  ac: 12; speed: 1; cchar: 'p'; hd: '8d4'   ; damage: '1 1 1d6|12 5 0d0'               ;
    level: 2),
(name: 'Novice Priest'            ;cmove: $07020002;spells: $0000108C;cdefense: $2030;
  sleep: 100;    mexp: 7;
  aaf: 20;  ac: 10; speed: 1; cchar: 'p'; hd: '7d4'   ; damage: '1 1 1d5'                        ;
    level: 2),
(name: 'Novice Mage'              ;cmove: $07020002;spells: $0000089C;cdefense: $2030;
  sleep: 50;    mexp: 7;
  aaf: 20;   ac: 6; speed: 1; cchar: 'p'; hd: '6d4'   ; damage: '1 1 1d4'                        ;
    level: 2),
(name: 'Yellow Mushroom patch'    ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 2;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '1d1'   ; damage: '4 13 1d6'                       ;
     level: 2),
(name: 'White Jelly'              ;cmove: $0B000001;spells: $00000000;cdefense: $01A0;
  sleep: 999;   mexp: 10;
   aaf: 2;   ac: 1; speed: 2; cchar: 'J'; hd: '8d8'   ; damage: '14 5 1d2'                       ;
     level: 2),
(name: 'Giant Green Frog'         ;cmove: $0000000A;spells: $00000000;cdefense: $0082;
  sleep: 300;    mexp: 6;
  aaf: 14;   ac: 8; speed: 1; cchar: 'f'; hd: '2d8'   ; damage: '1 2 1d3'                        ;
    level: 2),
(name: 'Giant Black Ant'          ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 400;    mexp: 8;
  aaf: 14;  ac: 20; speed: 1; cchar: 'a'; hd: '3d6'   ; damage: '1 2 1d4'                        ;
    level: 2),
(name: 'White Harpy'              ;cmove: $00000012;spells: $00000000;cdefense: $2036;
  sleep: 100;    mexp: 5;
  aaf: 16;  ac: 17; speed: 1; cchar: 'h'; hd: '2d5'   ; damage: '1 3 1d1|1 3 1d1|1 2 1d2'        ;
    level: 2),
(name: 'Blue Yeek'                ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 100;    mexp: 4;
  aaf: 18;  ac: 14; speed: 1; cchar: 'y'; hd: '2d6'   ; damage: '1 1 1d5'                        ;
    level: 2),
(name: 'Green Worm mass'          ;cmove: $00200022;spells: $00000000;cdefense: $01B0;
  sleep: 100;    mexp: 3;
   aaf: 7;   ac: 3; speed: 0; cchar: 'w'; hd: '6d4'   ; damage: '9 12 1d3'                       ;
     level: 2),
(name: 'Large Black Snake'        ;cmove: $0000000A;spells: $00000000;cdefense: $00B0;
  sleep: 750;    mexp: 9;
   aaf: 5;  ac: 38; speed: 0; cchar: 'R'; hd: '4d8'   ; damage: '1 2 1d4|1 16 1d6'               ;
     level: 2),
(name: 'Poltergeist'              ;cmove: $0F15003A;spells: $0000001F;cdefense: $100C;
  sleep: 750;    mexp: 6;
   aaf: 8;  ac: 15; speed: 3; cchar: 'G'; hd: '2d5'   ; damage: '4 1 1d1'                        ;
     level: 3),
(name: 'Metallic Blue Centipedes' ;cmove: $00000012;spells: $00000000;cdefense: $0000;
  sleep: 150;    mexp: 7;
   aaf: 6;   ac: 6; speed: 2; cchar: 'c'; hd: '4d5'   ; damage: '1 12 1d2'                       ;
     level: 3),
(name: 'Giant White Lice'         ;cmove: $00200022;spells: $00000000;cdefense: $01F0;
  sleep: 100;    mexp: 1;
   aaf: 6;   ac: 5; speed: 2; cchar: 'l'; hd: '1d1'   ; damage: '1 2 1d1'                        ;
     level: 3),
(name: 'Black Naga'               ;cmove: $0710000A;spells: $00000000;cdefense: $20E6;
  sleep: 1200;   mexp: 20;
  aaf: 16;  ac: 40; speed: 1; cchar: 'n'; hd: '6d8'   ; damage: '1 16 1d8'                       ;
    level: 3),
(name: 'Spotted Mushroom patch'   ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 3;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '1d1'   ; damage: '14 13 2d4'                      ;
     level: 3),
(name: 'Yellow Jelly'             ;cmove: $0B000001;spells: $0001000F;cdefense: $01A0;
  sleep: 999;   mexp: 12;
   aaf: 2;   ac: 1; speed: 2; cchar: 'J'; hd: '10d8'  ; damage: '14 5 1d3'                       ;
     level: 3),
(name: 'Scruffy looking Hobbit'   ;cmove: $05020002;spells: $00000000;cdefense: $2030;
  sleep: 100;    mexp: 4;
  aaf: 16;   ac: 8; speed: 1; cchar: 'p'; hd: '3d5'   ; damage: '1 1 1d4|12 5 0d0'               ;
    level: 3),
(name: 'Huge Brown Bat'           ;cmove: $00000022;spells: $00000000;cdefense: $2160;
  sleep: 400;    mexp: 4;
   aaf: 8;  ac: 12; speed: 3; cchar: 'b'; hd: '2d6'   ; damage: '1 2 1d2'                        ;
     level: 3),
(name: 'Giant White Ant'          ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 800;    mexp: 7;
   aaf: 8;  ac: 16; speed: 1; cchar: 'a'; hd: '3d6'   ; damage: '1 2 1d4'                        ;
     level: 3),
(name: 'Yellow Mold'              ;cmove: $0B000001;spells: $00000000;cdefense: $10A0;
  sleep: 999;    mexp: 9;
   aaf: 2;  ac: 10; speed: 1; cchar: 'm'; hd: '8d8'   ; damage: '1 1 1d4'                        ;
     level: 3),
(name: 'Metallic Red Centipedes'  ;cmove: $0000000A;spells: $00000000;cdefense: $0000;
  sleep: 200;   mexp: 12;
   aaf: 8;   ac: 9; speed: 2; cchar: 'c'; hd: '4d8'   ; damage: '1 12 1d2'                       ;
     level: 3),
(name: 'Yellow Worm mass'         ;cmove: $00200022;spells: $00000000;cdefense: $01B0;
  sleep: 100;    mexp: 4;
   aaf: 7;   ac: 4; speed: 0; cchar: 'w'; hd: '4d8'   ; damage: '15 12 1d3'                      ;
     level: 3),
(name: 'Large Grey Snake'         ;cmove: $0000000A;spells: $00000000;cdefense: $00B0;
  sleep: 700;   mexp: 10;
   aaf: 5;  ac: 40; speed: 0; cchar: 'R'; hd: '6d8'   ; damage: '1 2 1d4|1 16 1d6'               ;
     level: 3),
(name: 'Radiation Eye'            ;cmove: $00000001;spells: $0001000B;cdefense: $2102;
  sleep: 100;    mexp: 6;
   aaf: 2;   ac: 6; speed: 1; cchar: 'e'; hd: '3d6'   ; damage: '2 7 1d6'                        ;
     level: 3),
(name: 'Drooling Harpy'           ;cmove: $00000012;spells: $00000000;cdefense: $2036;
  sleep: 100;    mexp: 7;
  aaf: 16;  ac: 22; speed: 1; cchar: 'h'; hd: '2d8'   ; damage: '1 3 1d1|1 3 1d1|1 2 1d2|1 18 0d0';
    level: 3),
(name: 'Silver Mouse'             ;cmove: $0020000A;spells: $00000000;cdefense: $2072;
  sleep: 100;    mexp: 1;
   aaf: 8;   ac: 5; speed: 1; cchar: 'r'; hd: '1d1'   ; damage: '23 1 1d1'                       ;
     level: 4),
(name: 'Black Mushroom patch'     ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 8;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '8d8'   ; damage: '1 13 1d3'                       ;
     level: 4),
(name: 'Blue Jelly'               ;cmove: $0B000001;spells: $00000000;cdefense: $01A0;
  sleep: 999;   mexp: 14;
   aaf: 2;   ac: 1; speed: 1; cchar: 'J'; hd: '12d8'  ; damage: '7 5 1d6'                        ;
     level: 4),
(name: 'Creeping Copper Coins'    ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 100;    mexp: 9;
   aaf: 3;  ac: 24; speed: 0; cchar: '$'; hd: '7d8'   ; damage: '1 2 1d4|14 8 2d4'               ;
     level: 4),
(name: 'Giant White Rat'          ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 300;    mexp: 1;
   aaf: 8;   ac: 7; speed: 1; cchar: 'r'; hd: '2d2'   ; damage: '14 2 1d3'                       ;
     level: 4),
(name: 'Giant Black Centipede'    ;cmove: $00000022;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 11;
   aaf: 8;  ac: 20; speed: 1; cchar: 'c'; hd: '5d8'   ; damage: '1 2 1d2|1 4 1d2'                ;
     level: 4),
(name: 'Giant Blue Centipede'     ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 500;   mexp: 10;
   aaf: 8;  ac: 20; speed: 1; cchar: 'c'; hd: '4d8'   ; damage: '1 2 1d3|1 4 1d4'                ;
     level: 4),
(name: 'Blue Worm mass'           ;cmove: $00200022;spells: $00000000;cdefense: $01B0;
  sleep: 100;    mexp: 5;
   aaf: 7;  ac: 12; speed: 0; cchar: 'w'; hd: '5d8'   ; damage: '7 12 1d4'                       ;
     level: 4),
(name: 'Large Grey Snake'         ;cmove: $0000000A;spells: $00000000;cdefense: $00B0;
  sleep: 500;   mexp: 14;
   aaf: 6;  ac: 41; speed: 0; cchar: 'R'; hd: '6d8'   ; damage: '1 2 1d5|1 16 1d8'               ;
     level: 4),
(name: 'Jackal'                   ;cmove: $00000012;spells: $00000000;cdefense: $2030;
  sleep: 300;    mexp: 8;
  aaf: 12;  ac: 16; speed: 1; cchar: 'j'; hd: '3d8'   ; damage: '1 2 1d6'                        ;
    level: 4),
(name: 'Green Naga'               ;cmove: $0710000A;spells: $00000000;cdefense: $2066;
  sleep: 1200;   mexp: 30;
  aaf: 20;  ac: 40; speed: 1; cchar: 'n'; hd: '9d8'   ; damage: '1 16 1d8|6 9 2d6'               ;
    level: 5),
(name: 'Green Glutton Ghost'      ;cmove: $0F150032;spells: $0000003F;cdefense: $100C;
  sleep: 100;   mexp: 15;
  aaf: 10;  ac: 20; speed: 3; cchar: 'G'; hd: '3d6'   ; damage: '22 15 1d1'                      ;
    level: 5),
(name: 'White Mushroom patch'     ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;    mexp: 5;
   aaf: 2;   ac: 1; speed: 1; cchar: ','; hd: '1d1'   ; damage: '11 13 2d4'                      ;
     level: 5),
(name: 'Green Jelly'              ;cmove: $0B000001;spells: $00000000;cdefense: $01A0;
  sleep: 999;   mexp: 18;
   aaf: 2;   ac: 1; speed: 2; cchar: 'J'; hd: '22d8'  ; damage: '9 5 1d2'                        ;
     level: 5),
(name: 'Skeleton Kobold'          ;cmove: $00020002;spells: $00000000;cdefense: $000C;
  sleep: 400;   mexp: 12;
  aaf: 20;  ac: 26; speed: 1; cchar: 's'; hd: '5d8'   ; damage: '1 1 1d6'                        ;
    level: 5),
(name: 'Silver Jelly'             ;cmove: $0B000001;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 15;
   aaf: 2;  ac: 25; speed: 1; cchar: 'J'; hd: '20d8'  ; damage: '23 5 1d3'                       ;
     level: 5),
(name: 'Giant Black Frog'         ;cmove: $0000000A;spells: $00000000;cdefense: $00A2;
  sleep: 400;   mexp: 12;
  aaf: 12;  ac: 18; speed: 1; cchar: 'f'; hd: '4d8'   ; damage: '1 2 1d6'                        ;
    level: 5),
(name: 'Grey Icky-Thing'          ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 150;   mexp: 10;
  aaf: 14;  ac: 12; speed: 1; cchar: 'i'; hd: '4d8'   ; damage: '1 5 1d5'                        ;
    level: 5),
(name: 'Disenchanter Eye'         ;cmove: $00000009;spells: $00010009;cdefense: $2102;
  sleep: 100;   mexp: 20;
   aaf: 4;  ac: 10; speed: 0; cchar: 'e'; hd: '7d8'   ; damage: '21 7 0d0'                       ;
     level: 5),
(name: 'Black Yeek'               ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 100;    mexp: 8;
  aaf: 18;  ac: 16; speed: 1; cchar: 'y'; hd: '2d8'   ; damage: '1 1 1d5'                        ;
    level: 5),
(name: 'Red Worm mass'            ;cmove: $00200022;spells: $00000000;cdefense: $21B0;
  sleep: 100;    mexp: 6;
   aaf: 7;  ac: 12; speed: 0; cchar: 'w'; hd: '5d8'   ; damage: '5 12 1d6'                       ;
     level: 5),
(name: 'Giant House Fly'          ;cmove: $00000022;spells: $00000000;cdefense: $0062;
  sleep: 200;   mexp: 10;
  aaf: 12;  ac: 16; speed: 3; cchar: 'F'; hd: '3d8'   ; damage: '1 2 1d2'                        ;
    level: 5),
(name: 'Copperhead Snake'         ;cmove: $00000012;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 15;
   aaf: 6;  ac: 20; speed: 1; cchar: 'R'; hd: '4d6'   ; damage: '14 2 2d4'                       ;
     level: 5),
(name: 'Rot Jelly'                ;cmove: $0B000001;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 15;
   aaf: 2;  ac: 30; speed: 1; cchar: 'J'; hd: '20d8'  ; damage: '22 5 2d3'                       ;
     level: 5),
(name: 'Purple Mushroom patch'    ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 0;   mexp: 12;
   aaf: 2;   ac: 1; speed: 2; cchar: ','; hd: '1d1'   ; damage: '16 13 1d2'                      ;
     level: 6),
(name: 'Brown Mold'               ;cmove: $0B000001;spells: $00000000;cdefense: $10A0;
  sleep: 999;   mexp: 20;
   aaf: 2;  ac: 12; speed: 1; cchar: 'm'; hd: '15d8'  ; damage: '3 1 1d4'                        ;
     level: 6),
(name: 'Giant Brown Bat'          ;cmove: $0000001A;spells: $00000000;cdefense: $2160;
  sleep: 300;   mexp: 10;
  aaf: 10;  ac: 15; speed: 3; cchar: 'b'; hd: '3d8'   ; damage: '1 2 1d3'                        ;
    level: 6),
(name: 'Creeping Silver Coins'    ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 100;   mexp: 18;
   aaf: 4;  ac: 30; speed: 0; cchar: '$'; hd: '12d8'  ; damage: '1 2 1d6|14 8 2d6'               ;
     level: 6),
(name: 'Orc'                      ;cmove: $0B020002;spells: $00000000;cdefense: $2036;
  sleep: 300;   mexp: 16;
  aaf: 20;  ac: 32; speed: 1; cchar: 'o'; hd: '9d8'   ; damage: '1 1 1d8'                        ;
    level: 6),
(name: 'Grey Harpy'               ;cmove: $00000012;spells: $00000000;cdefense: $2036;
  sleep: 100;   mexp: 14;
  aaf: 16;  ac: 20; speed: 2; cchar: 'h'; hd: '3d8'   ; damage: '1 3 1d2|1 3 1d2|1 2 1d2'        ;
    level: 6),
(name: 'Blue Icky-Thing'          ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 12;
  aaf: 18;  ac: 14; speed: 1; cchar: 'i'; hd: '4d8'   ; damage: '7 5 2d3'                        ;
    level: 6),
(name: 'Rattlesnake'              ;cmove: $00000012;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 20;
   aaf: 6;  ac: 24; speed: 1; cchar: 'R'; hd: '6d7'   ; damage: '14 2 2d5'                       ;
     level: 6),
(name: 'Bloodshot Eye'            ;cmove: $00000001;spells: $00010007;cdefense: $2102;
  sleep: 100;   mexp: 15;
   aaf: 2;   ac: 6; speed: 1; cchar: 'e'; hd: '4d8'   ; damage: '10 7 2d6'                       ;
     level: 7),
(name: 'Red Naga'                 ;cmove: $0710000A;spells: $00000000;cdefense: $20E6;
  sleep: 1200;   mexp: 40;
  aaf: 20;  ac: 40; speed: 1; cchar: 'n'; hd: '11d8'  ; damage: '1 16 1d10|2 2 1d4'              ;
    level: 7),
(name: 'Red Jelly'                ;cmove: $0B000001;spells: $00000000;cdefense: $01A0;
  sleep: 999;   mexp: 26;
   aaf: 2;   ac: 1; speed: 1; cchar: 'J'; hd: '26d8'  ; damage: '2 5 1d5'                        ;
     level: 7),
(name: 'Giant Red Frog'           ;cmove: $0000000A;spells: $00000000;cdefense: $00A2;
  sleep: 500;   mexp: 16;
  aaf: 12;  ac: 16; speed: 1; cchar: 'f'; hd: '5d8'   ; damage: '2 2 2d4'                        ;
    level: 7),
(name: 'Green Icky-Thing'         ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 18;
  aaf: 14;  ac: 12; speed: 1; cchar: 'i'; hd: '5d8'   ; damage: '9 5 2d5'                        ;
    level: 7),
(name: 'Zombie Kobold'            ;cmove: $00020002;spells: $00000000;cdefense: $002E;
  sleep: 300;   mexp: 14;
  aaf: 20;  ac: 14; speed: 1; cchar: 'z'; hd: '6d8'   ; damage: '1 1 1d2|1 1 1d2'                ;
    level: 7),
(name: 'Lost Soul'                ;cmove: $0015001A;spells: $0001002F;cdefense: $100C;
  sleep: 100;   mexp: 18;
   aaf: 4;  ac: 10; speed: 1; cchar: 'G'; hd: '2d8'   ; damage: '1 1 2d2|18 5 0d0'               ;
     level: 7),
(name: 'Greedy little Gnome'      ;cmove: $0B020002;spells: $00000000;cdefense: $2030;
  sleep: 100;   mexp: 13;
  aaf: 18;  ac: 14; speed: 1; cchar: 'p'; hd: '3d8'   ; damage: '1 1 1d7|13 5 0d0'               ;
    level: 7),
(name: 'Giant Green Fly'          ;cmove: $00000022;spells: $00000000;cdefense: $0062;
  sleep: 500;   mexp: 15;
  aaf: 12;  ac: 14; speed: 2; cchar: 'F'; hd: '3d8'   ; damage: '1 2 1d4'                        ;
    level: 7),
(name: 'Brown Yeek'               ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 100;   mexp: 11;
  aaf: 18;  ac: 18; speed: 1; cchar: 'y'; hd: '3d8'   ; damage: '1 1 1d6'                        ;
    level: 8),
(name: 'Green Mold'               ;cmove: $0B000001;spells: $00000000;cdefense: $10A0;
  sleep: 750;   mexp: 28;
   aaf: 2;  ac: 14; speed: 1; cchar: 'm'; hd: '21d8'  ; damage: '4 1 1d4'                        ;
     level: 8),
(name: 'Skeleton Orc'             ;cmove: $00020002;spells: $00000000;cdefense: $100C;
  sleep: 400;   mexp: 26;
  aaf: 20;  ac: 36; speed: 1; cchar: 's'; hd: '10d8'  ; damage: '1 1 2d5'                        ;
    level: 8),
(name: 'Seedy looking Human'      ;cmove: $13020002;spells: $00000000;cdefense: $2034;
  sleep: 200;   mexp: 22;
  aaf: 20;  ac: 26; speed: 1; cchar: 'p'; hd: '8d8'   ; damage: '1 1 3d4'                        ;
    level: 8),
(name: 'Red Icky-Thing'           ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 22;
  aaf: 14;  ac: 18; speed: 2; cchar: 'i'; hd: '4d8'   ; damage: '1 5 1d3|6 8 1d5'                ;
    level: 8),
(name: 'Bandit'                   ;cmove: $13020002;spells: $00000000;cdefense: $2030;
  sleep: 999;   mexp: 26;
  aaf: 20;  ac: 24; speed: 1; cchar: 'p'; hd: '8d8'   ; damage: '1 1 2d4|12 5 0d0'               ;
    level: 8),
(name: 'Yeti'                     ;cmove: $00020002;spells: $00000000;cdefense: $2024;
  sleep: 100;   mexp: 30;
  aaf: 20;  ac: 24; speed: 1; cchar: 'Y'; hd: '11d8'  ; damage: '1 3 1d3|1 3 1d3|1 2 1d4'        ;
    level: 9),
(name: 'Bloodshot Icky-Thing'     ;cmove: $0000000A;spells: $0001000B;cdefense: $2022;
  sleep: 800;   mexp: 24;
  aaf: 14;  ac: 18; speed: 1; cchar: 'i'; hd: '7d8'   ; damage: '1 5 1d4|9 8 2d4'                ;
    level: 9),
(name: 'Giant Grey Rat'           ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 200;    mexp: 2;
  aaf: 10;  ac: 12; speed: 1; cchar: 'r'; hd: '2d3'   ; damage: '14 2 1d4'                       ;
    level: 9),
(name: 'Black Harpy'              ;cmove: $0000000A;spells: $00000000;cdefense: $2036;
  sleep: 100;   mexp: 19;
  aaf: 16;  ac: 22; speed: 2; cchar: 'h'; hd: '3d8'   ; damage: '1 3 1d2|1 3 1d2|1 2 1d3'        ;
    level: 9),
(name: 'Giant Black Bat'          ;cmove: $00000012;spells: $00000000;cdefense: $2060;
  sleep: 250;   mexp: 16;
  aaf: 12;  ac: 18; speed: 3; cchar: 'b'; hd: '2d8'   ; damage: '1 2 1d6'                        ;
    level: 9),
(name: 'Clear Yeek'               ;cmove: $07030002;spells: $00000000;cdefense: $0030;
  sleep: 100;   mexp: 14;
  aaf: 18;  ac: 24; speed: 1; cchar: 'y'; hd: '3d6'   ; damage: '1 1 1d5'                        ;
    level: 9),
(name: 'Orc Shaman'               ;cmove: $0B020002;spells: $00008085;cdefense: $2036;
  sleep: 200;   mexp: 30;
  aaf: 20;  ac: 15; speed: 1; cchar: 'o'; hd: '7d8'   ; damage: '1 1 1d6'                        ;
    level: 9),
(name: 'Giant Red Ant'            ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 600;   mexp: 22;
  aaf: 12;  ac: 34; speed: 1; cchar: 'a'; hd: '4d8'   ; damage: '1 2 1d4|2 4 1d4'                ;
    level: 9),
(name: 'King Cobra'               ;cmove: $00000012;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 28;
   aaf: 8;  ac: 30; speed: 1; cchar: 'R'; hd: '8d8'   ; damage: '10 9 1d2|14 2 3d4'              ;
     level: 9),
(name: 'Clear Mushroom patch'     ;cmove: $00210001;spells: $00000000;cdefense: $00A0;
  sleep: 0;    mexp: 1;
   aaf: 4;   ac: 1; speed: 2; cchar: ','; hd: '1d1'   ; damage: '1 13 1d1'                       ;
     level: 10),
(name: 'Giant White Tick'         ;cmove: $0000000A;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 27;
  aaf: 12;  ac: 40; speed: 0; cchar: 't'; hd: '15d8'  ; damage: '14 2 2d6'                       ;
    level: 10),
(name: 'Hairy Mold'               ;cmove: $0B000001;spells: $00000000;cdefense: $10A0;
  sleep: 700;   mexp: 32;
   aaf: 2;  ac: 15; speed: 1; cchar: 'm'; hd: '15d8'  ; damage: '14 1 1d3'                       ;
     level: 10),
(name: 'Disenchanter Mold'        ;cmove: $0B000001;spells: $0001000B;cdefense: $10A0;
  sleep: 100;   mexp: 40;
   aaf: 2;  ac: 20; speed: 1; cchar: 'm'; hd: '16d8'  ; damage: '21 5 1d6'                       ;
     level: 10),
(name: 'Giant Red Centipede'      ;cmove: $00000002;spells: $00000000;cdefense: $0082;
  sleep: 500;   mexp: 24;
  aaf: 12;  ac: 26; speed: 2; cchar: 'c'; hd: '3d8'   ; damage: '1 2 1d2|14 4 1d2'               ;
    level: 10),
(name: 'Creeping Gold Coins'      ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 100;   mexp: 32;
   aaf: 5;  ac: 36; speed: 0; cchar: '$'; hd: '18d8'  ; damage: '1 2 2d5|14 8 3d5'               ;
     level: 10),
(name: 'Giant Fruit Fly'          ;cmove: $00200022;spells: $00000000;cdefense: $0062;
  sleep: 500;    mexp: 4;
   aaf: 8;  ac: 14; speed: 2; cchar: 'F'; hd: '2d2'   ; damage: '1 2 1d2'                        ;
     level: 10),
(name: 'Brigand'                  ;cmove: $13020002;spells: $00000000;cdefense: $2030;
  sleep: 100;   mexp: 35;
  aaf: 20;  ac: 32; speed: 1; cchar: 'p'; hd: '9d8'   ; damage: '1 1 2d4|13 5 0d0'               ;
    level: 10),
(name: 'Orc Zombie'               ;cmove: $00020002;spells: $00000000;cdefense: $102E;
  sleep: 250;   mexp: 30;
  aaf: 20;  ac: 24; speed: 1; cchar: 'z'; hd: '11d8'  ; damage: '1 1 1d4|1 1 1d4'                ;
    level: 11),
(name: 'Orc Warrior'              ;cmove: $0F020002;spells: $00000000;cdefense: $2036;
  sleep: 250;   mexp: 34;
  aaf: 20;  ac: 36; speed: 1; cchar: 'o'; hd: '11d8'  ; damage: '1 1 2d6'                        ;
    level: 11),
(name: 'Vorpal Bunny'             ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 300;    mexp: 2;
   aaf: 8;  ac: 10; speed: 2; cchar: 'r'; hd: '2d3'   ; damage: '1 2 1d5'                        ;
     level: 11),
(name: 'Nasty little Gnome'       ;cmove: $0B020002;spells: $000020B5;cdefense: $2030;
  sleep: 10;   mexp: 32;
  aaf: 18;  ac: 10; speed: 1; cchar: 'p'; hd: '4d8'   ; damage: '1 1 1d5'                        ;
    level: 11),
(name: 'Hobgoblin'                ;cmove: $0F020002;spells: $00000000;cdefense: $2036;
  sleep: 300;   mexp: 38;
  aaf: 20;  ac: 38; speed: 1; cchar: 'H'; hd: '12d8'  ; damage: '1 1 1d10'                       ;
    level: 11),
(name: 'Black Mamba'              ;cmove: $00000012;spells: $00000000;cdefense: $00B0;
  sleep: 1;   mexp: 40;
  aaf: 20;  ac: 32; speed: 2; cchar: 'R'; hd: '10d8'  ; damage: '14 2 4d4'                       ;
    level: 12),
(name: 'Grape Jelly'              ;cmove: $0B000001;spells: $0001000B;cdefense: $01A0;
  sleep: 999;   mexp: 60;
   aaf: 2;   ac: 1; speed: 1; cchar: 'J'; hd: '52d8'  ; damage: '19 5 5d8'                       ;
     level: 12),
(name: 'Master Yeek'              ;cmove: $07020002;spells: $00008018;cdefense: $2030;
  sleep: 100;   mexp: 28;
  aaf: 18;  ac: 24; speed: 1; cchar: 'y'; hd: '5d8'   ; damage: '1 1 1d8'                        ;
    level: 12),
(name: 'Priest'                   ;cmove: $13020002;spells: $00000285;cdefense: $2030;
  sleep: 400;   mexp: 36;
  aaf: 20;  ac: 22; speed: 1; cchar: 'p'; hd: '7d8'   ; damage: '1 1 2d3'                        ;
    level: 12),
(name: 'Giant Clear Ant'          ;cmove: $00010002;spells: $00000000;cdefense: $0102;
  sleep: 600;   mexp: 24;
  aaf: 12;  ac: 18; speed: 1; cchar: 'a'; hd: '3d7'   ; damage: '1 2 1d4'                        ;
    level: 12),
(name: 'Air Spirit'               ;cmove: $00030022;spells: $00000000;cdefense: $0010;
  sleep: 200;   mexp: 40;
  aaf: 12;  ac: 20; speed: 3; cchar: 'E'; hd: '5d8'   ; damage: '1 1 1d3'                        ;
    level: 12),
(name: 'Skeleton Human'           ;cmove: $00020002;spells: $00000000;cdefense: $100C;
  sleep: 300;   mexp: 38;
  aaf: 20;  ac: 30; speed: 1; cchar: 's'; hd: '12d8'  ; damage: '1 1 1d8'                        ;
    level: 12),
(name: 'Human Zombie'             ;cmove: $00020002;spells: $00000000;cdefense: $102E;
  sleep: 200;   mexp: 34;
  aaf: 20;  ac: 24; speed: 1; cchar: 'z'; hd: '11d8'  ; damage: '1 1 1d4|1 1 1d4'                ;
    level: 12),
(name: 'Moaning Spirit'           ;cmove: $0F15000A;spells: $0001002E;cdefense: $100C;
  sleep: 300;   mexp: 44;
   aaf: 6;  ac: 20; speed: 1; cchar: 'G'; hd: '4d8'   ; damage: '4 10 0d0|15 5 1d8'              ;
     level: 12),
(name: 'Swordsman'                ;cmove: $13020002;spells: $00000000;cdefense: $2030;
  sleep: 999;   mexp: 40;
  aaf: 20;  ac: 34; speed: 1; cchar: 'p'; hd: '11d8'  ; damage: '1 1 3d5'                        ;
    level: 12),
(name: 'Killer Brown Beetle'      ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 38;
  aaf: 10;  ac: 40; speed: 1; cchar: 'K'; hd: '13d8'  ; damage: '1 2 3d4'                        ;
    level: 13),
(name: 'Ogre'                     ;cmove: $07020002;spells: $00000000;cdefense: $2036;
  sleep: 300;   mexp: 42;
  aaf: 20;  ac: 32; speed: 1; cchar: 'o'; hd: '13d8'  ; damage: '1 1 2d8'                        ;
    level: 13),
(name: 'Giant Red Speckled Frog'  ;cmove: $0000000A;spells: $00000000;cdefense: $00A2;
  sleep: 300;   mexp: 32;
  aaf: 12;  ac: 20; speed: 1; cchar: 'f'; hd: '6d8'   ; damage: '1 2 3d4'                        ;
    level: 13),
(name: 'Magic User'               ;cmove: $13020002;spells: $00002413;cdefense: $2030;
  sleep: 100;   mexp: 35;
  aaf: 20;  ac: 10; speed: 1; cchar: 'p'; hd: '7d8'   ; damage: '1 1 2d2'                        ;
    level: 13),
(name: 'Black Orc'                ;cmove: $0B020002;spells: $00000000;cdefense: $2036;
  sleep: 200;   mexp: 40;
  aaf: 20;  ac: 36; speed: 1; cchar: 'o'; hd: '12d8'  ; damage: '1 1 3d4'                        ;
    level: 13),
(name: 'Giant Long-Eared Bat'     ;cmove: $0000001A;spells: $00000000;cdefense: $2160;
  sleep: 200;   mexp: 20;
  aaf: 12;  ac: 20; speed: 3; cchar: 'b'; hd: '5d8'   ; damage: '1 2 1d4|1 3 1d2|1 3 1d2'        ;
    level: 13),
(name: 'Giant Gnat'               ;cmove: $00200022;spells: $00000000;cdefense: $0062;
  sleep: 100;    mexp: 1;
   aaf: 8;   ac: 4; speed: 3; cchar: 'F'; hd: '1d2'   ; damage: '1 2 1d1'                        ;
     level: 13),
(name: 'Killer Green Beetle'      ;cmove: $00000012;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 46;
  aaf: 12;  ac: 45; speed: 1; cchar: 'K'; hd: '16d8'  ; damage: '1 2 4d4'                        ;
    level: 14),
(name: 'Giant Flea'               ;cmove: $00200022;spells: $00000000;cdefense: $0062;
  sleep: 100;    mexp: 1;
   aaf: 8;  ac: 25; speed: 2; cchar: 'F'; hd: '2d2'   ; damage: '1 2 1d2'                        ;
     level: 14),
(name: 'Giant White Dragon Fly'   ;cmove: $00000012;spells: $0040000A;cdefense: $0060;
  sleep: 500;   mexp: 54;
  aaf: 20;  ac: 20; speed: 1; cchar: 'F'; hd: '5d8'   ; damage: '7 2 1d6'                        ;
    level: 14),
(name: 'Hill Giant'               ;cmove: $07020002;spells: $00000000;cdefense: $2034;
  sleep: 500;   mexp: 52;
  aaf: 20;  ac: 36; speed: 1; cchar: 'P'; hd: '16d8'  ; damage: '1 1 3d6'                        ;
    level: 14),
(name: 'Skeleton Hobgoblin'       ;cmove: $00020002;spells: $00000000;cdefense: $100C;
  sleep: 300;   mexp: 46;
  aaf: 20;  ac: 34; speed: 1; cchar: 's'; hd: '13d8'  ; damage: '1 1 2d5'                        ;
    level: 14),
(name: 'Flesh Golem'              ;cmove: $00020002;spells: $00000000;cdefense: $11B0;
  sleep: 100;   mexp: 48;
  aaf: 12;  ac: 10; speed: 1; cchar: 'g'; hd: '12d8'  ; damage: '1 1 1d6|1 1 1d6'                ;
    level: 14),
(name: 'White Dragon Bat'         ;cmove: $00000012;spells: $00400004;cdefense: $2150;
  sleep: 500;   mexp: 40;
  aaf: 12;  ac: 20; speed: 3; cchar: 'b'; hd: '2d6'   ; damage: '7 2 1d3'                        ;
    level: 14),
(name: 'Giant Black Lice'         ;cmove: $00200012;spells: $00000000;cdefense: $01F2;
  sleep: 100;    mexp: 1;
   aaf: 6;   ac: 7; speed: 2; cchar: 'l'; hd: '1d1'   ; damage: '1 2 1d2'                        ;
     level: 14),
(name: 'Guardian Naga'            ;cmove: $1710000A;spells: $00000000;cdefense: $20E6;
  sleep: 1200;   mexp: 60;
  aaf: 20;  ac: 50; speed: 1; cchar: 'n'; hd: '24d8'  ; damage: '1 16 2d8|1 2 1d8'               ;
    level: 15),
(name: 'Giant Grey Bat'           ;cmove: $00000012;spells: $00000000;cdefense: $2160;
  sleep: 150;   mexp: 22;
  aaf: 12;  ac: 22; speed: 3; cchar: 'b'; hd: '4d8'   ; damage: '1 2 1d6|1 3 1d2|1 3 1d2'        ;
    level: 15),
(name: 'Giant Clear Centipede'    ;cmove: $00010002;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 30;
  aaf: 10;  ac: 30; speed: 1; cchar: 'c'; hd: '5d8'   ; damage: '1 2 2d4|1 4 2d4'                ;
    level: 15),
(name: 'Giant Yellow Tick'        ;cmove: $0000000A;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 48;
  aaf: 12;  ac: 48; speed: 0; cchar: 't'; hd: '20d8'  ; damage: '14 2 3d9'                       ;
    level: 15),
(name: 'Giant Ebony Ant'          ;cmove: $00200002;spells: $00000000;cdefense: $0002;
  sleep: 600;    mexp: 3;
  aaf: 12;  ac: 24; speed: 1; cchar: 'a'; hd: '3d4'   ; damage: '1 2 2d3'                        ;
    level: 15),
(name: 'Frost Giant'              ;cmove: $07020002;spells: $00000000;cdefense: $0024;
  sleep: 500;   mexp: 54;
  aaf: 20;  ac: 38; speed: 1; cchar: 'P'; hd: '17d8'  ; damage: '7 1 3d6'                        ;
    level: 15),
(name: 'Clay Golem'               ;cmove: $00020002;spells: $00000000;cdefense: $1200;
  sleep: 100;   mexp: 50;
  aaf: 12;  ac: 20; speed: 1; cchar: 'g'; hd: '14d8'  ; damage: '1 1 1d8|1 1 1d8'                ;
    level: 15),
(name: 'Huge White Bat'           ;cmove: $00200012;spells: $00000000;cdefense: $2160;
  sleep: 400;    mexp: 3;
   aaf: 7;  ac: 12; speed: 2; cchar: 'b'; hd: '3d8'   ; damage: '1 2 1d6'                        ;
     level: 15),
(name: 'Giant Tan Bat'            ;cmove: $00000012;spells: $00000000;cdefense: $2160;
  sleep: 400;   mexp: 18;
  aaf: 12;  ac: 18; speed: 2; cchar: 'b'; hd: '3d8'   ; damage: '4 2 1d2|1 3 1d1|1 3 1d1'        ;
    level: 15),
(name: 'Violet Mold'              ;cmove: $0B000001;spells: $00010009;cdefense: $10A0;
  sleep: 700;   mexp: 50;
   aaf: 2;  ac: 15; speed: 1; cchar: 'm'; hd: '17d8'  ; damage: '11 1 1d2'                       ;
     level: 15),
(name: 'Umber Hulk'               ;cmove: $00020002;spells: $00000000;cdefense: $2126;
  sleep: 100;   mexp: 75;
  aaf: 20;  ac: 20; speed: 1; cchar: 'U'; hd: '20d8'  ; damage: '3 7 0d0|1 1 1d6|1 1 1d6|1 2 2d6';
    level: 16),
(name: 'Gelatinous Cube'          ;cmove: $2F18000A;spells: $00000000;cdefense: $00A2;
  sleep: 1;   mexp: 36;
  aaf: 12;  ac: 18; speed: 0; cchar: 'C'; hd: '45d8'  ; damage: '6 5 1d10'                       ;
    level: 16),
(name: 'Giant Black Rat'          ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 200;    mexp: 3;
   aaf: 8;  ac: 16; speed: 1; cchar: 'r'; hd: '3d4'   ; damage: '14 2 1d5'                       ;
     level: 16),
(name: 'Giant Green Dragon Fly'   ;cmove: $00000012;spells: $0010000A;cdefense: $0070;
  sleep: 500;   mexp: 58;
  aaf: 20;  ac: 20; speed: 1; cchar: 'F'; hd: '5d8'   ; damage: '14 2 1d6'                       ;
    level: 16),
(name: 'Fire Giant'               ;cmove: $07020002;spells: $00000000;cdefense: $2014;
  sleep: 500;   mexp: 62;
  aaf: 20;  ac: 40; speed: 1; cchar: 'P'; hd: '20d8'  ; damage: '5 1 3d7'                        ;
    level: 16),
(name: 'Green Dragon Bat'         ;cmove: $00000012;spells: $00100004;cdefense: $2150;
  sleep: 500;   mexp: 44;
  aaf: 12;  ac: 22; speed: 3; cchar: 'b'; hd: '2d7'   ; damage: '14 2 1d3'                       ;
    level: 16),
(name: 'Quasit'                   ;cmove: $1103000A;spells: $000010FA;cdefense: $0004;
  sleep: 200;   mexp: 48;
  aaf: 20;  ac: 30; speed: 1; cchar: 'q'; hd: '5d8'   ; damage: '15 2 1d6|1 3 1d3|1 3 1d3'       ;
    level: 16),
(name: 'Troll'                    ;cmove: $07020002;spells: $00000000;cdefense: $2026;
  sleep: 400;   mexp: 64;
  aaf: 20;  ac: 40; speed: 1; cchar: 'T'; hd: '17d8'  ; damage: '1 1 1d4|1 1 1d4|1 2 1d6'        ;
    level: 17),
(name: 'Water Spirit'             ;cmove: $0000000A;spells: $00000000;cdefense: $0020;
  sleep: 400;   mexp: 58;
  aaf: 12;  ac: 28; speed: 2; cchar: 'E'; hd: '8d8'   ; damage: '1 1 2d4'                        ;
    level: 17),
(name: 'Giant Brown Scorpion'     ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 200;   mexp: 62;
  aaf: 14;  ac: 44; speed: 1; cchar: 'S'; hd: '11d8'  ; damage: '1 2 2d4|2 4 1d7'                ;
    level: 17),
(name: 'Earth Spirit'             ;cmove: $0000000A;spells: $00000000;cdefense: $0200;
  sleep: 500;   mexp: 64;
  aaf: 10;  ac: 40; speed: 1; cchar: 'E'; hd: '13d8'  ; damage: '1 1 1d8|1 1 1d8'                ;
    level: 17),
(name: 'Fire Spirit'              ;cmove: $00000002;spells: $00000000;cdefense: $2010;
  sleep: 200;   mexp: 66;
  aaf: 20;  ac: 30; speed: 2; cchar: 'E'; hd: '10d8'  ; damage: '5 1 2d6'                        ;
    level: 18),
(name: 'Urik-Hai Orc'             ;cmove: $0B020002;spells: $00000000;cdefense: $2036;
  sleep: 200;   mexp: 68;
  aaf: 20;  ac: 42; speed: 1; cchar: 'o'; hd: '14d8'  ; damage: '1 1 3d5'                        ;
    level: 18),
(name: 'Stone Giant'              ;cmove: $07020002;spells: $00000000;cdefense: $2204;
  sleep: 500;   mexp: 80;
  aaf: 20;  ac: 40; speed: 1; cchar: 'P'; hd: '22d8'  ; damage: '1 1 3d8'                        ;
    level: 18),
(name: 'Stone Golem'              ;cmove: $00020002;spells: $00000000;cdefense: $1200;
  sleep: 100;  mexp: 100;
  aaf: 12;  ac: 75; speed: 0; cchar: 'g'; hd: '28d8'  ; damage: '1 1 1d10|1 1 1d10'              ;
    level: 19),
(name: 'Grey Ooze'                ;cmove: $071A0022;spells: $00000000;cdefense: $00A2;
  sleep: 1;   mexp: 40;
  aaf: 15;  ac: 10; speed: 1; cchar: 'O'; hd: '6d8'   ; damage: '7 5 2d6'                        ;
    level: 19),
(name: 'Disenchanter Ooze'        ;cmove: $071A0022;spells: $00000000;cdefense: $00A2;
  sleep: 1;   mexp: 50;
  aaf: 15;  ac: 15; speed: 1; cchar: 'O'; hd: '6d8'   ; damage: '21 5 0d0'                       ;
    level: 19),
(name: 'Giant Spotted Rat'        ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 200;    mexp: 3;
   aaf: 8;  ac: 20; speed: 1; cchar: 'r'; hd: '4d3'   ; damage: '14 2 1d5'                       ;
     level: 19),
(name: 'Mummified Kobold'         ;cmove: $0B020002;spells: $00000000;cdefense: $102C;
  sleep: 750;   mexp: 46;
  aaf: 20;  ac: 24; speed: 1; cchar: 'M'; hd: '13d8'  ; damage: '1 1 1d6|1 1 1d6'                ;
    level: 19),
(name: 'Killer Black Beetle'      ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 75;
  aaf: 14;  ac: 46; speed: 1; cchar: 'K'; hd: '18d8'  ; damage: '1 2 4d5'                        ;
    level: 19),
(name: 'Red Mold'                 ;cmove: $0B000001;spells: $00000000;cdefense: $30A0;
  sleep: 700;   mexp: 64;
   aaf: 2;  ac: 16; speed: 1; cchar: 'm'; hd: '17d8'  ; damage: '5 5 4d4'                        ;
     level: 19),
(name: 'Quythulg'                 ;cmove: $00010000;spells: $00002010;cdefense: $5000;
  sleep: 0;  mexp: 200;
  aaf: 10;   ac: 1; speed: 1; cchar: 'Q'; hd: '4d8'   ; damage: '0 0 0d0'                        ;
    level: 20),
(name: 'Giant Red Bat'            ;cmove: $0000000A;spells: $00000000;cdefense: $2060;
  sleep: 200;   mexp: 40;
  aaf: 12;  ac: 24; speed: 2; cchar: 'b'; hd: '5d8'   ; damage: '1 2 1d7|1 3 1d3|1 3 1d3'        ;
    level: 20),
(name: 'Giant Black Dragon Fly'   ;cmove: $00000012;spells: $00200009;cdefense: $0072;
  sleep: 500;   mexp: 58;
  aaf: 20;  ac: 22; speed: 1; cchar: 'F'; hd: '4d8'   ; damage: '10 2 1d6'                       ;
    level: 20),
(name: 'Cloud Giant'              ;cmove: $07020002;spells: $00000000;cdefense: $2134;
  sleep: 500;  mexp: 125;
  aaf: 20;  ac: 44; speed: 1; cchar: 'P'; hd: '24d8'  ; damage: '8 1 3d8'                        ;
    level: 20),
(name: 'Black Dragon Bat'         ;cmove: $00000012;spells: $00200004;cdefense: $2150;
  sleep: 500;   mexp: 50;
  aaf: 12;  ac: 24; speed: 3; cchar: 'b'; hd: '2d8'   ; damage: '6 2 1d3'                        ;
    level: 21),
(name: 'Blue Dragon Bat'          ;cmove: $00000012;spells: $00080004;cdefense: $2150;
  sleep: 500;   mexp: 54;
  aaf: 12;  ac: 26; speed: 3; cchar: 'b'; hd: '3d6'   ; damage: '8 2 1d3'                        ;
    level: 21),
(name: 'Mummified Orc'            ;cmove: $0B020002;spells: $00000000;cdefense: $102C;
  sleep: 750;   mexp: 56;
  aaf: 20;  ac: 28; speed: 1; cchar: 'M'; hd: '14d8'  ; damage: '1 1 2d4|1 1 2d4'                ;
    level: 21),
(name: 'Killer Boring Beetle'     ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 70;
  aaf: 12;  ac: 48; speed: 1; cchar: 'K'; hd: '18d8'  ; damage: '1 2 4d5'                        ;
    level: 21),
(name: 'Killer Stag Beetle'       ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 80;
  aaf: 12;  ac: 50; speed: 1; cchar: 'K'; hd: '20d8'  ; damage: '1 2 3d4|1 1 1d12'               ;
    level: 22),
(name: 'Black Mold'               ;cmove: $0B000081;spells: $00000000;cdefense: $10A0;
  sleep: 500;   mexp: 68;
   aaf: 2;  ac: 18; speed: 1; cchar: 'm'; hd: '15d8'  ; damage: '1 1 4d3'                        ;
     level: 22),
(name: 'Iron Golem'               ;cmove: $00020002;spells: $00000000;cdefense: $1080;
  sleep: 100;  mexp: 160;
  aaf: 12;  ac: 99;speed: -1; cchar: 'g'; hd: '80d8'  ; damage: '1 1 1d12|1 1 1d12'              ;
    level: 22),
(name: 'Giant Yellow Scorpion'    ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 200;   mexp: 60;
  aaf: 12;  ac: 38; speed: 1; cchar: 'S'; hd: '12d8'  ; damage: '1 2 1d8|14 4 2d5'               ;
    level: 22),
(name: 'Green Ooze'               ;cmove: $00200001;spells: $00000000;cdefense: $00B2;
  sleep: 1;    mexp: 6;
  aaf: 15;   ac: 5; speed: 0; cchar: 'O'; hd: '4d8'   ; damage: '6 5 2d3'                        ;
    level: 22),
(name: 'Black Ooze'               ;cmove: $003A0012;spells: $0001000B;cdefense: $0192;
  sleep: 1;    mexp: 7;
  aaf: 10;   ac: 6;speed: -1; cchar: 'O'; hd: '6d8'   ; damage: '9 5 2d6'                        ;
    level: 23),
(name: 'Warrior'                  ;cmove: $13120002;spells: $00000000;cdefense: $2030;
  sleep: 400;   mexp: 60;
  aaf: 20;  ac: 40; speed: 1; cchar: 'p'; hd: '15d8'  ; damage: '1 1 3d5'                        ;
    level: 23),
(name: 'Red Dragon Bat'           ;cmove: $00000012;spells: $00800004;cdefense: $2150;
  sleep: 500;   mexp: 60;
  aaf: 12;  ac: 28; speed: 3; cchar: 'b'; hd: '3d8'   ; damage: '5 2 1d3'                        ;
    level: 23),
(name: 'Killer Blue Beetle'       ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 85;
  aaf: 15;  ac: 50; speed: 1; cchar: 'K'; hd: '20d8'  ; damage: '1 2 4d5'                        ;
    level: 23),
(name: 'Giant Silver Ant'         ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 600;   mexp: 45;
  aaf: 15;  ac: 38; speed: 1; cchar: 'a'; hd: '6d8'   ; damage: '6 2 4d4'                        ;
    level: 23),
(name: 'Crimson Mold'             ;cmove: $0B000001;spells: $00000000;cdefense: $10A0;
  sleep: 500;   mexp: 65;
   aaf: 2;  ac: 18; speed: 1; cchar: 'm'; hd: '16d8'  ; damage: '1 1 1d3|4 5 0d0'                ;
     level: 23),
(name: 'Forest Wight'             ;cmove: $0F00000A;spells: $0000100F;cdefense: $112E;
  sleep: 300;  mexp: 140;
  aaf: 20;  ac: 30; speed: 1; cchar: 'W'; hd: '12d8'  ; damage: '1 1 1d6|1 1 1d6|19 5 12d8'      ;
    level: 24),
(name: 'Berzerker'                ;cmove: $07020002;spells: $00000000;cdefense: $2030;
  sleep: 100;   mexp: 65;
  aaf: 20;  ac: 20; speed: 1; cchar: 'p'; hd: '15d8'  ; damage: '1 1 1d8|1 1 1d8'                ;
    level: 24),
(name: 'Mummified Human'          ;cmove: $0B020002;spells: $00000000;cdefense: $102C;
  sleep: 600;   mexp: 70;
  aaf: 20;  ac: 34; speed: 1; cchar: 'M'; hd: '17d8'  ; damage: '1 1 2d4|1 1 2d4'                ;
    level: 24),
(name: 'Banshee'                  ;cmove: $0F15001A;spells: $0001002F;cdefense: $100C;
  sleep: 100;   mexp: 60;
  aaf: 20;  ac: 24; speed: 2; cchar: 'G'; hd: '6d8'   ; damage: '4 10 0d0|19 5 14d8'             ;
    level: 24),
(name: 'Giant Troll'              ;cmove: $0F020002;spells: $00000000;cdefense: $2026;
  sleep: 500;   mexp: 85;
  aaf: 20;  ac: 40; speed: 1; cchar: 'T'; hd: '19d8'  ; damage: '1 1 1d6|1 1 1d6|1 2 3d4'        ;
    level: 25),
(name: 'Giant Brown Tick'         ;cmove: $00000012;spells: $00000000;cdefense: $0022;
  sleep: 200;   mexp: 70;
  aaf: 12;  ac: 50; speed: 0; cchar: 't'; hd: '18d8'  ; damage: '14 2 1d10|10 4 1d1'             ;
    level: 25),
(name: 'Killer Red Beetle'        ;cmove: $00000012;spells: $00000000;cdefense: $0002;
  sleep: 300;   mexp: 85;
  aaf: 15;  ac: 50; speed: 1; cchar: 'K'; hd: '20d8'  ; damage: '2 2 4d4'                        ;
    level: 25),
(name: 'Wooden Mold'              ;cmove: $00000001;spells: $00000000;cdefense: $10A0;
  sleep: 999;  mexp: 100;
   aaf: 2;  ac: 50; speed: 1; cchar: 'm'; hd: '25d8'  ; damage: '14 8 2d6'                       ;
     level: 25),
(name: 'Giant Blue Dragon Fly'    ;cmove: $00000012;spells: $00080009;cdefense: $0030;
  sleep: 500;   mexp: 75;
  aaf: 20;  ac: 24; speed: 1; cchar: 'F'; hd: '6d8'   ; damage: '1 2 1d6'                        ;
    level: 25),
(name: 'Giant Grey Ant Lion'      ;cmove: $0008000A;spells: $00000000;cdefense: $0032;
  sleep: 400;   mexp: 90;
  aaf: 10;  ac: 40; speed: 1; cchar: 'A'; hd: '19d8'  ; damage: '1 2 2d12'                       ;
    level: 26),
(name: 'Disenchanter Bat'         ;cmove: $00000012;spells: $00000000;cdefense: $2060;
  sleep: 1;   mexp: 75;
  aaf: 14;  ac: 24; speed: 3; cchar: 'b'; hd: '4d8'   ; damage: '21 1 0d0'                       ;
    level: 26),
(name: 'Giant Fire Tick'          ;cmove: $0000000A;spells: $00000000;cdefense: $2012;
  sleep: 200;   mexp: 90;
  aaf: 14;  ac: 54; speed: 1; cchar: 't'; hd: '16d8'  ; damage: '5 9 3d7'                        ;
    level: 26),
(name: 'White Wraith'             ;cmove: $0F02000A;spells: $00000000;cdefense: $112E;
  sleep: 100;  mexp: 165;
  aaf: 20;  ac: 40; speed: 1; cchar: 'W'; hd: '15d8'  ; damage: '1 1 1d6|1 1 1d6|19 5 15d8'      ;
    level: 26),
(name: 'Giant Black Scorpion'     ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 200;   mexp: 85;
  aaf: 12;  ac: 50; speed: 1; cchar: 'S'; hd: '13d8'  ; damage: '1 2 1d10|14 4 2d5'              ;
    level: 26),
(name: 'Clear Ooze'               ;cmove: $000B000A;spells: $00000000;cdefense: $00B2;
  sleep: 1;   mexp: 12;
  aaf: 10;  ac: 14; speed: 1; cchar: 'O'; hd: '4d8'   ; damage: '3 5 1d8'                        ;
    level: 26),
(name: 'Killer Fire Beetle'       ;cmove: $00000012;spells: $00000000;cdefense: $2012;
  sleep: 300;   mexp: 95;
  aaf: 14;  ac: 45; speed: 1; cchar: 'K'; hd: '13d8'  ; damage: '1 2 3d4|5 9 4d5'                ;
    level: 27),
(name: 'Vampire'                  ;cmove: $17000002;spells: $00001209;cdefense: $112E;
  sleep: 100;  mexp: 175;
  aaf: 20;  ac: 45; speed: 1; cchar: 'V'; hd: '20d8'  ; damage: '1 1 1d6|1 1 1d6|19 5 18d8'      ;
    level: 27),
(name: 'Giant Red Dragon Fly'     ;cmove: $00000012;spells: $00800008;cdefense: $2050;
  sleep: 500;   mexp: 75;
  aaf: 20;  ac: 24; speed: 1; cchar: 'F'; hd: '7d8'   ; damage: '4 2 1d6'                        ;
    level: 27),
(name: 'Shimmering Mold'          ;cmove: $0B000081;spells: $00000000;cdefense: $10A0;
  sleep: 100;  mexp: 180;
   aaf: 2;  ac: 24; speed: 1; cchar: 'm'; hd: '32d8'  ; damage: '8 5 5d4'                        ;
     level: 27),
(name: 'Black Knight'             ;cmove: $17020002;spells: $0000010F;cdefense: $2030;
  sleep: 100;  mexp: 140;
  aaf: 20;  ac: 60; speed: 1; cchar: 'p'; hd: '25d8'  ; damage: '1 1 5d5'                        ;
    level: 28),
(name: 'Mage'                     ;cmove: $13020002;spells: $00002C73;cdefense: $2030;
  sleep: 100;  mexp: 150;
  aaf: 20;  ac: 30; speed: 1; cchar: 'p'; hd: '10d8'  ; damage: '1 1 2d5'                        ;
    level: 28),
(name: 'Ice Troll'                ;cmove: $0F020002;spells: $00000000;cdefense: $0026;
  sleep: 500;  mexp: 160;
  aaf: 20;  ac: 46; speed: 1; cchar: 'T'; hd: '22d8'  ; damage: '1 1 1d5|1 1 1d5|7 2 3d6'        ;
    level: 28),
(name: 'Giant Purple Worm'        ;cmove: $0000000A;spells: $00000000;cdefense: $2030;
  sleep: 300;  mexp: 400;
  aaf: 14;  ac: 65; speed: 1; cchar: 'w'; hd: '65d8'  ; damage: '1 1 1d8|6 2 2d8|14 4 1d8'       ;
    level: 29),
(name: 'Young Blue Dragon'        ;cmove: $1F00000A;spells: $0008100B;cdefense: $2005;
  sleep: 700;  mexp: 300;
  aaf: 20;  ac: 50; speed: 1; cchar: 'd'; hd: '33d8'  ; damage: '1 3 1d4|1 3 1d4|1 2 1d6'        ;
    level: 29),
(name: 'Young White Dragon'       ;cmove: $1F00000A;spells: $0040100B;cdefense: $2005;
  sleep: 700;  mexp: 275;
  aaf: 20;  ac: 50; speed: 1; cchar: 'd'; hd: '32d8'  ; damage: '1 3 1d4|1 3 1d4|1 2 1d6'        ;
    level: 29),
(name: 'Young Green Dragon'       ;cmove: $1F00000A;spells: $0010100B;cdefense: $2005;
  sleep: 700;  mexp: 290;
  aaf: 20;  ac: 50; speed: 1; cchar: 'd'; hd: '32d8'  ; damage: '1 3 1d4|1 3 1d4|1 2 1d6'        ;
    level: 29),
(name: 'Giant Fire Bat'           ;cmove: $00000012;spells: $00000000;cdefense: $2050;
  sleep: 100;   mexp: 85;
  aaf: 14;  ac: 30; speed: 2; cchar: 'b'; hd: '5d8'   ; damage: '5 2 3d6|1 3 1d4|1 3 1d4'        ;
    level: 29),
(name: 'Giant Glowing Rat'        ;cmove: $0020000A;spells: $00000000;cdefense: $2070;
  sleep: 200;    mexp: 4;
   aaf: 8;  ac: 24; speed: 1; cchar: 'r'; hd: '3d3'   ; damage: '8 2 2d6'                        ;
     level: 29),
	{ Now things are going to get tough...                  }
	{ Some of the creatures have Max hit points, denoted in }
	{ their CDEFENSE flags as the '4000' bit set            }
(name: 'Skeleton Troll'           ;cmove: $00020002;spells: $00000000;cdefense: $500C;
  sleep: 400;  mexp: 225;
  aaf: 20;  ac: 55; speed: 1; cchar: 's'; hd: '14d8'  ; damage: '1 1 1d6|1 1 1d6|1 2 3d4'        ;
    level: 30),
(name: 'Giant Lightning Bat'      ;cmove: $0000000A;spells: $00000000;cdefense: $2042;
  sleep: 100;   mexp: 80;
  aaf: 15;  ac: 34; speed: 2; cchar: 'b'; hd: '8d8'   ; damage: '8 2 3d8|1 3 1d5|1 3 1d5'        ;
    level: 30),
(name: 'Giant Static Ant'         ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 600;   mexp: 80;
  aaf: 10;  ac: 40; speed: 1; cchar: 'a'; hd: '8d8'   ; damage: '8 2 5d5'                        ;
    level: 30),
(name: 'Grave Wight'              ;cmove: $0F02000A;spells: $0000190A;cdefense: $512E;
  sleep: 300;  mexp: 325;
  aaf: 20;  ac: 35; speed: 1; cchar: 'W'; hd: '12d8'  ; damage: '1 1 1d7|1 1 1d7|19 5 20d8'      ;
    level: 30),
(name: 'Killer Slicer Beetle'     ;cmove: $0000000A;spells: $00000000;cdefense: $0012;
  sleep: 300;  mexp: 200;
  aaf: 14;  ac: 55; speed: 1; cchar: 'K'; hd: '22d8'  ; damage: '1 2 5d8'                        ;
    level: 30),
(name: 'Giant White Ant Lion'     ;cmove: $0008000A;spells: $00000000;cdefense: $0022;
  sleep: 400;  mexp: 175;
  aaf: 12;  ac: 45; speed: 1; cchar: 'A'; hd: '20d8'  ; damage: '7 2 3d10'                       ;
    level: 30),
(name: 'Ghost'                    ;cmove: $1715000A;spells: $0001002F;cdefense: $500C;
  sleep: 100;  mexp: 350;
  aaf: 20;  ac: 30; speed: 2; cchar: 'G'; hd: '13d8'  ; damage: '4 7 0d0|19 5 22d8|17 3 1d10'    ;
    level: 31),
(name: 'Giant Black Ant Lion'     ;cmove: $0008000A;spells: $00000000;cdefense: $0032;
  sleep: 400;  mexp: 170;
  aaf: 14;  ac: 45; speed: 1; cchar: 'A'; hd: '23d8'  ; damage: '1 2 2d12|6 9 3d6'               ;
    level: 31),
(name: 'Death Watch Beetle'       ;cmove: $0000000A;spells: $00000000;cdefense: $0012;
  sleep: 300;  mexp: 190;
  aaf: 16;  ac: 60; speed: 1; cchar: 'K'; hd: '25d8'  ; damage: '1 2 5d4|1 10 5d6'               ;
    level: 31),
(name: 'Ogre Magi'                ;cmove: $07020002;spells: $0000A356;cdefense: $403C;
  sleep: 300;  mexp: 250;
  aaf: 20;  ac: 42; speed: 1; cchar: 'o'; hd: '14d8'  ; damage: '1 1 3d6'                        ;
    level: 31),
(name: 'Crystal Ooze'             ;cmove: $07390009;spells: $00000000;cdefense: $0092;
  sleep: 600;    mexp: 8;
   aaf: 5;  ac: 30;speed: -1; cchar: 'O'; hd: '12d8'  ; damage: '7 5 4d4'                        ;
     level: 31),
(name: 'Two-Headed Troll'         ;cmove: $0F020002;spells: $00000000;cdefense: $6026;
  sleep: 500;  mexp: 275;
  aaf: 20;  ac: 48; speed: 1; cchar: 'T'; hd: '14d8'  ; damage: '1 1 1d8|1 1 1d8|1 2 1d6|1 2 1d6';
    level: 32),
(name: 'Invisible Stalker'        ;cmove: $00030022;spells: $00000000;cdefense: $0000;
  sleep: 200;  mexp: 200;
  aaf: 20;  ac: 46; speed: 3; cchar: 'E'; hd: '19d8'  ; damage: '1 1 1d6'                        ;
    level: 32),
(name: 'Giant Hunter Ant'         ;cmove: $00000002;spells: $00000000;cdefense: $0002;
  sleep: 10;  mexp: 150;
  aaf: 16;  ac: 40; speed: 1; cchar: 'a'; hd: '12d8'   ; damage: '1 2 4d8'                        ;
    level: 32),
(name: 'Ninja'                    ;cmove: $0F020002;spells: $00000000;cdefense: $6030;
  sleep: 100;  mexp: 300;
  aaf: 20;  ac: 65; speed: 1; cchar: 'p'; hd: '15d8'  ; damage: '14 1 3d4|2 1 3d4'               ;
    level: 32),
(name: 'Barrow Wight'             ;cmove: $0F02000A;spells: $00001308;cdefense: $512E;
  sleep: 100;  mexp: 375;
  aaf: 20;  ac: 40; speed: 1; cchar: 'W'; hd: '13d8'  ; damage: '1 1 1d8|1 1 1d8|19 5 26d8'      ;
    level: 33),
(name: 'Skeleton 2-Headed Troll'  ;cmove: $00020002;spells: $00000000;cdefense: $500C;
  sleep: 200;  mexp: 325;
  aaf: 20;  ac: 48; speed: 1; cchar: 's'; hd: '20d8'  ; damage: '1 1 1d9|1 1 1d9|1 2 1d5|1 2 1d5';
    level: 33),
(name: 'Water Elemental'          ;cmove: $0000000A;spells: $00000000;cdefense: $0020;
  sleep: 500;  mexp: 325;
  aaf: 12;  ac: 36; speed: 1; cchar: 'E'; hd: '25d8'  ; damage: '1 1 1d10|1 1 1d10'              ;
    level: 33),
(name: 'Fire Elemental'           ;cmove: $000A0012;spells: $00000000;cdefense: $2010;
  sleep: 700;  mexp: 350;
  aaf: 16;  ac: 40; speed: 0; cchar: 'E'; hd: '25d8'  ; damage: '5 1 4d6'                        ;
    level: 33),
(name: 'Lich'                     ;cmove: $1F020002;spells: $00019F75;cdefense: $500C;
  sleep: 600;  mexp: 750;
  aaf: 20;  ac: 50; speed: 1; cchar: 'L'; hd: '25d8'  ; damage: '15 5 2d8|19 5 30d8|24 5 0d0'    ;
    level: 34),
(name: 'Master Vampire'           ;cmove: $17000002;spells: $00001307;cdefense: $512E;
  sleep: 100;  mexp: 700;
  aaf: 20;  ac: 55; speed: 1; cchar: 'V'; hd: '23d8'  ; damage: '1 1 1d6|1 1 1d6|19 5 32d8'      ;
    level: 34),
(name: 'Spirit Troll'             ;cmove: $00040002;spells: $00000000;cdefense: $402E;
  sleep: 100;  mexp: 425;
  aaf: 20;  ac: 56; speed: 1; cchar: 'T'; hd: '15d8'  ; damage: '1 3 1d5|1 3 1d5|1 2 1d6'        ;
    level: 34),
(name: 'Giant Red Scorpion'       ;cmove: $0000000A;spells: $00000000;cdefense: $0002;
  sleep: 400;  mexp: 275;
  aaf: 12;  ac: 50; speed: 2; cchar: 'S'; hd: '18d8'  ; damage: '1 2 1d6|14 4 1d4'               ;
    level: 34),
(name: 'Earth Elemental'          ;cmove: $001A0002;spells: $00000000;cdefense: $0200;
  sleep: 900;  mexp: 375;
  aaf: 10;  ac: 60; speed: 0; cchar: 'E'; hd: '30d8'  ; damage: '1 1 4d6|1 1 4d6'                ;
    level: 34),
(name: 'Young Black Dragon'       ;cmove: $1F00000A;spells: $0020100B;cdefense: $6005;
  sleep: 500;  mexp: 600;
  aaf: 20;  ac: 55; speed: 1; cchar: 'd'; hd: '32d8'  ; damage: '1 3 1d5|1 3 1d5|1 2 1d6'        ;
    level: 35),
(name: 'Young Red Dragon'         ;cmove: $1F00000A;spells: $0080100A;cdefense: $6015;
  sleep: 500;  mexp: 650;
  aaf: 20;  ac: 60; speed: 1; cchar: 'd'; hd: '36d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d8'        ;
    level: 35),
(name: 'Necromancer'              ;cmove: $13020002;spells: $00005762;cdefense: $6030;
  sleep: 100;  mexp: 600;
  aaf: 20;  ac: 40; speed: 1; cchar: 'p'; hd: '17d8'  ; damage: '1 1 2d6'                        ;
    level: 35),
(name: 'Mummified Troll'          ;cmove: $0F020002;spells: $00000000;cdefense: $502C;
  sleep: 500;  mexp: 400;
  aaf: 20;  ac: 38; speed: 1; cchar: 'M'; hd: '18d8'  ; damage: '1 1 2d6|1 1 2d6'                ;
    level: 35),
(name: 'Giant Red Ant Lion'       ;cmove: $00080009;spells: $00000000;cdefense: $0032;
  sleep: 400;  mexp: 350;
  aaf: 14;  ac: 48; speed: 1; cchar: 'A'; hd: '23d8'  ; damage: '5 2 3d12'                       ;
    level: 35),
(name: 'Mature White Dragon'      ;cmove: $2F00000A;spells: $0040100A;cdefense: $4005;
  sleep: 700; mexp: 1000;
  aaf: 20;  ac: 65; speed: 1; cchar: 'd'; hd: '48d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d8'        ;
    level: 35),
(name: 'Xorn'                     ;cmove: $00160002;spells: $00000000;cdefense: $4200;
  sleep: 100;  mexp: 650;
  aaf: 20;  ac: 80; speed: 1; cchar: 'X'; hd: '20d8'  ; damage: '1 1 1d6|1 1 1d6|1 1 1d6'        ;
    level: 36),
(name: 'Giant Mottled Ant Lion'   ;cmove: $0008000A;spells: $00000000;cdefense: $0032;
  sleep: 400;  mexp: 350;
  aaf: 14;  ac: 50; speed: 2; cchar: 'A'; hd: '24d8 ' ; damage: '1 2 2d10'                       ;
    level: 36),
(name: 'Grey Wraith'              ;cmove: $0F02000A;spells: $00011308;cdefense: $512E;
  sleep: 100;  mexp: 700;
  aaf: 20;  ac: 50; speed: 1; cchar: 'W'; hd: '23d8'  ; damage: '1 1 1d10|1 1 1d10|19 5 34d8'    ;
    level: 36),
(name: 'Young Multi-Hued Dragon'  ;cmove: $7F00000A;spells: $00F81005;cdefense: $6005;
  sleep: 500; mexp: 1250;
  aaf: 20;  ac: 55; speed: 1; cchar: 'd'; hd: '40d8'  ; damage: '1 3 1d9|1 3 1d9|1 2 2d10'       ;
    level: 36),
(name: 'Mature Blue Dragon'       ;cmove: $2F00000A;spells: $00081009;cdefense: $6005;
  sleep: 400; mexp: 1200;
  aaf: 20;  ac: 75; speed: 1; cchar: 'd'; hd: '48d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d10'       ;
    level: 36),
(name: 'Mature Green Dragon'      ;cmove: $1F00000A;spells: $0010100A;cdefense: $6005;
  sleep: 700; mexp: 1100;
  aaf: 20;  ac: 70; speed: 1; cchar: 'd'; hd: '48d8'  ; damage: '1 3 1d4|1 3 1d4|1 2 1d6'        ;
    level: 36),
(name: 'Iridescent Beetle'        ;cmove: $0000000A;spells: $00000000;cdefense: $0012;
  sleep: 300;  mexp: 850;
  aaf: 16;  ac: 60; speed: 1; cchar: 'K'; hd: '32d8'  ; damage: '1 2 4d6|1 1 1d12|11 7 0d0'      ;
    level: 37),
(name: 'King Vampire'             ;cmove: $17000002;spells: $00001307;cdefense: $512E;
  sleep: 100; mexp: 1000;
  aaf: 20;  ac: 65; speed: 1; cchar: 'V'; hd: '38d8'  ; damage: '1 1 1d6|1 1 1d6|19 5 38d8'      ;
    level: 37),
(name: 'King Lich'                ;cmove: $1F020002;spells: $00019F73;cdefense: $500C;
  sleep: 500; mexp: 1400;
  aaf: 20;  ac: 65; speed: 1; cchar: 'L'; hd: '52d8'  ; damage: '15 5 2d10|19 5 36d8|24 5 0d0'   ;
    level: 37),
(name: 'Mature Red Dragon'        ;cmove: $2F00000A;spells: $00801808;cdefense: $6015;
  sleep: 300; mexp: 1400;
  aaf: 20;  ac: 80; speed: 1; cchar: 'd'; hd: '60d8'  ; damage: '1 3 1d10|1 3 1d10|1 2 2d12'     ;
    level: 37),
(name: 'Mature Black Dragon'      ;cmove: $2F00000A;spells: $00201009;cdefense: $6005;
  sleep: 700; mexp: 1350;
  aaf: 20;  ac: 55; speed: 1; cchar: 'd'; hd: '58d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d10'       ;
    level: 37),
(name: 'Mature Multi-Hued Dragon' ;cmove: $7F00000A;spells: $00F81A05;cdefense: $6005;
  sleep: 500; mexp: 1650;
  aaf: 20;  ac: 65; speed: 1; cchar: 'd'; hd: '80d8'  ; damage: '1 3 1d10|1 3 1d10|1 2 2d12'     ;
    level: 38),
(name: 'Ancient White Dragon'     ;cmove: $4F000002;spells: $00401A08;cdefense: $4005;
  sleep: 800; mexp: 1500;
  aaf: 20;  ac: 80; speed: 2; cchar: 'D'; hd: '88d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d8'        ;
    level: 38),
(name: 'Emperor Wight'            ;cmove: $1B02000A;spells: $00001306;cdefense: $512E;
  sleep: 100; mexp: 1600;
  aaf: 20;  ac: 40; speed: 2; cchar: 'W'; hd: '48d8'  ; damage: '1 1 1d12|1 1 1d12|19 5 42d8'    ;
    level: 38),
(name: 'Black Wraith'             ;cmove: $1F02000A;spells: $00001307;cdefense: $512E;
  sleep: 100; mexp: 1700;
  aaf: 20;  ac: 55; speed: 1; cchar: 'W'; hd: '50d8'  ; damage: '1 1 1d12|1 1 1d12|19 5 44d8'    ;
    level: 38),
(name: 'Nether Wraith'            ;cmove: $1F07000A;spells: $00005316;cdefense: $512E;
  sleep: 100; mexp: 2100;
  aaf: 20;  ac: 55; speed: 1; cchar: 'W'; hd: '58d8'  ; damage: '1 1 1d12|1 1 1d12|19 5 52d8'    ;
    level: 39),
(name: 'Sorcerer'                 ;cmove: $13020002;spells: $0000FF73;cdefense: $6030;
  sleep: 100; mexp: 2150;
  aaf: 20;  ac: 50; speed: 2; cchar: 'p'; hd: '30d8'  ; damage: '1 1 2d8'                        ;
    level: 39),
(name: 'Ancient Blue Dragon'      ;cmove: $4F000002;spells: $00081A08;cdefense: $6005;
  sleep: 800; mexp: 2500;
  aaf: 20;  ac: 90; speed: 2; cchar: 'D'; hd: '87d8'  ; damage: '1 3 1d9|1 3 1d9|1 2 2d12'       ;
    level: 39),
(name: 'Ancient Green Dragon'     ;cmove: $4F000002;spells: $00101A09;cdefense: $6005;
  sleep: 700; mexp: 2400;
  aaf: 20;  ac: 85; speed: 2; cchar: 'D'; hd: '90d8'  ; damage: '1 3 1d8|1 3 1d8|1 2 2d10'       ;
    level: 39),
(name: 'Ancient Black Dragon'     ;cmove: $4F000002;spells: $00201A07;cdefense: $6005;
  sleep: 700; mexp: 2500;
  aaf: 20;  ac: 90; speed: 2; cchar: 'D'; hd: '90d8'  ; damage: '1 3 1d9|1 3 1d9|1 2 2d10'       ;
    level: 39),
(name: 'Disenchanter Worms'       ;cmove: $00200022;spells: $00000000;cdefense: $01B0;
  sleep: 100;   mexp: 30;
   aaf: 5;   ac: 5; speed: 0; cchar: 'w'; hd: '10d8'  ; damage: '21 12 1d4'                      ;
     level: 40),
(name: 'Rotting Quylthulg'        ;cmove: $00010000;spells: $00004010;cdefense: $5000;
  sleep: 0; mexp: 1000;
  aaf: 20;   ac: 1; speed: 2; cchar: 'Q'; hd: '12d8'  ; damage: '0 0 0d0'                        ;
    level: 40),
(name: 'Ancient Red Dragon'       ;cmove: $7F000002;spells: $00801E06;cdefense: $6015;
  sleep: 500; mexp: 2750;
  aaf: 20; ac: 100; speed: 2; cchar: 'D'; hd: '105d8' ; damage: '1 3 1d10|1 3 1d10|1 2 2d14'     ;
    level: 40),
(name: 'Death Quasit'             ;cmove: $1103000A;spells: $000010FA;cdefense: $0004;
  sleep: 0; mexp: 1000;
  aaf: 20;  ac: 80; speed: 3; cchar: 'q'; hd: '55d8'  ; damage: '15 2 3d6|1 3 3d3|1 3 3d3'       ;
    level: 40),
(name: 'Emperor Lich'             ;cmove: $2F020002;spells: $00019F72;cdefense: $500C;
  sleep: 500;mexp: 10000;
  aaf: 20;  ac: 75; speed: 2; cchar: 'L'; hd: '190d8' ; damage: '15 5 2d12|19 5 46d8|24 5 0d0'   ;
    level: 40),
(name: 'Ancient Multi-Hued Dragon';cmove: $7F000002;spells: $00F89E05;cdefense: $6005;
  sleep: 500;mexp: 12000;
  aaf: 20; ac: 100; speed: 2; cchar: 'D'; hd: '260d8' ; damage: '1 3 1d12|1 3 1d12|1 2 3d12'     ;
    level: 40),
	{ Winning creatures should follow here.                         }
	{ Winning creatures are denoted by the 32 bit in CMOVE          }
	{ Iggy is not a win creature, just a royal pain in the ass...   }
(name: 'Evil Iggy'                ;cmove: $7F130002;spells: $0001D713;cdefense: $5004;
  sleep: 0;mexp: 18000;
  aaf: 20;  ac: 80; speed: 2; cchar: 'p'; hd: '300d8' ; damage: '2 1 4d6|13 19 0d0'               ;
    level: 50),
	{ Here is the only actual win creature...                       }
(name: 'Balrog'                   ;cmove: $FF1F0002;spells: $0081C743;cdefense: $5004;
  sleep: 0;mexp: 55000;
  aaf: 20; ac: 125; speed: 3; cchar: 'B'; hd: '375d8' ; damage: '5 1 10d12|1 17 8d12|24 5 0d0'    ;
    level: 100)
				);

	blank_monster	:  
			  monster_type =  (hp: 0;csleep: 0;cdis: 0;mptr: 0;nptr: 0;cspeed: 0;fy: 0;fx: 0;stuned: 0;ml:
			    false;confused: false);
