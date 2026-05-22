	{ Attempt to open the intro file			-RAK-	}
procedure intro(var finam : vtype);
      var
	xpos,i1                         : integer;
	dummy                           : char;
	day_test,in_line                : vtype;
	file1                           : text;
	file2                           : file of key_type;
	exit_flag                       : boolean;
      begin
	exit_flag := false;
	clear(1,1);
	{ Attempt to read hours.dat.  If it does not exist,     }
	{ then create a standard one.                           }
	priv_switch(1);
	open(file1,file_name:=MORIA_HOU,
		history:=readonly,sharing:=readonly);
	if (status(file1) = 0) then
	  begin
	    reset(file1);
	    repeat
	      readln(file1,in_line);
	      if (length(in_line) > 3) then
		begin
		  day_test := substr(in_line,1,4);
		  if      (day_test = 'SUN:') then days[1] := in_line
		  else if (day_test = 'MON:') then days[2] := in_line
		  else if (day_test = 'TUE:') then days[3] := in_line
		  else if (day_test = 'WED:') then days[4] := in_line
		  else if (day_test = 'THU:') then days[5] := in_line
		  else if (day_test = 'FRI:') then days[6] := in_line
		  else if (day_test = 'SAT:') then days[7] := in_line;
		end;
	    until(eof(file1));
	    close(file1);
	    priv_switch(0);
	  end
	else    { Create a standard hours file                  }
	  begin
	    priv_switch(0);
	    open(file1,file_name:=MORIA_HOU,
		organization:=sequential,history:=new,
		sharing:=readwrite);
	    if (status(file1) = 0) then
	      begin
		rewrite(file1);
		writeln(file1,'    Moria operating hours are:');
		writeln(file1,'    |    AM     |    PM     |');
		writeln(file1,'    1         111         111');
		writeln(file1,'    2123456789012123456789012');
		for i1 := 1 to 7 do
		  writeln(file1,days[i1]);
		writeln(file1,'       (X=Open; .=Closed)');
		close(file1);
		writeln('Created ',MORIA_HOU);
		exit_flag := true;
	      end
	    else
	      begin
		writeln('Error in creating ',MORIA_HOU);
		exit;
	      end;
	  end;

	{ Check the hours, if closed then require password	}
	if (not(exit_flag)) then
	  begin
	    xpos := index(finam,'/WIZARD');
	    if ( xpos > 0) then
	      if (check_pswd) then
		insert_str(finam,'/WIZARD','');
	    if (not(wizard1)) then
	      no_controly;
	    if (not(check_time)) then
	      if (not(wizard1)) then
		begin
		  priv_switch(1);
		  open(file1,file_name:=MORIA_HOU,
			history:=readonly,sharing:=readonly);
		  if (status(file1) = 0) then
		    begin
		      reset(file1);
		      repeat
			readln(file1,in_line);
			writeln(in_line);
		      until(eof(file1));
		      close(file1);
		    end;
		  priv_switch(0);
		  exit;
		end;
	  end;

	{ Print the introduction message, news, ect...		}
	priv_switch(1);
	open(file1,file_name:=MORIA_MOR,
		organization:=sequential,history:=readonly,
		sharing:=readwrite);
	if (status(file1) = 0) then
	  begin
	    if (not(exit_flag)) then
	      begin
		reset(file1);
		repeat
		  readln(file1,in_line);
		  writeln(in_line);
		until (eof(file1));
		pause_exit(24,0);
		close(file1);
	      end
	    else
	      close(file1);
	    priv_switch(0);
	  end
	else    { Create one...                                 }
	  begin
	    priv_switch(0);
	    open(file1,file_name:=MORIA_MOR,
		organization:=sequential,history:=new,
		sharing:=readwrite);
	    if (status(file1) = 0) then
	      begin
		rewrite(file1);
writeln(file1,'                         *********************');
writeln(file1,'                         **    Moria ',cur_version:4:2,'   **');
writeln(file1,'                         *********************');
writeln(file1,'                   COPYRIGHT (c) Robert Alan Koeneke');
writeln(file1,' ');
writeln(file1,'Programers : Robert Alan Koeneke / University of Oklahoma');
writeln(file1,'             Jimmey Wayne Todd   / University of Oklahoma');
writeln(file1,' ');
writeln(file1,'Dungeon Master: This file may contain updates and news.');
		close(file1);
		writeln('Created ',MORIA_MOR);
		exit_flag := true;
	      end
	    else
	      begin
		writeln('Error in creating ',MORIA_MOR);
		exit;
	      end;
	  end;
	{ Check for MASTER.DAT                          }
	priv_switch(1);
	open (file2,file_name:=moria_mas,
		access_method:=keyed,organization:=indexed,history:=readonly,
		sharing:=readwrite);
	if (status(file2) <> 0) then
	  begin
	    priv_switch(0);
	    open (file2,file_name:=moria_mas,
		access_method:=keyed,organization:=indexed,history:=new,
		sharing:=readwrite);
	    if (status(file2) = 0) then
	      begin
		writeln('Created ',MORIA_MAS);
		close(file2);
		exit_flag := true;
	      end
	    else
	      begin
		writeln('Error in creating ',MORIA_MAS);
		exit;
	      end;
	  end
	else
	  begin
	    close(file2);
	    priv_switch(0);
	  end;
	{ Check for TOPTWENTY.DAT                       }
	priv_switch(1);
	open (file1,file_name:=moria_top,
		organization:=sequential,history:=readonly,
		sharing:=readwrite);
	if ((status(file1) <> 0) and (status(file1) <> 2)) then
	  begin
	    priv_switch(0);
	    open (file1,file_name:=moria_top,
		organization:=sequential,history:=new,
		sharing:=readwrite);
	    if (status(file1) = 0) then
	      begin
		writeln('Created ',MORIA_TOP);
		close(file1);
		exit_flag := true;
	      end
	    else
	      begin
		writeln('Error in creating ',MORIA_TOP);
		exit;
	      end;
	  end
	else
	  begin
	    close(file1);
	    priv_switch(0);
	  end;
	if (exit_flag) then
	  begin
	    writeln('Notice: System MORIA wizard should set the protection');
	    writeln('        on  files  just created.  See INSTALL.HLP for');
	    writeln('        help on setting protection on the files.');
	    writeln('Notice: File HOURS.DAT may be edited to set operating');
	    writeln('        hours for MORIA.');
	    writeln('Notice: File MORIA.DAT may be edited to contain  news');
	    writeln('        items, etc...');
	    exit;
	  end;
      end;


	{ Prints dungeon map to external file			-RAK-	}
procedure print_map;
    var
	i1,i2,i3,i4,i5,i6,i7,i8         : integer;
	dun_line                        : string[133];
	filename1                       : string[80];
	tmp                             : char;
	file1                           : text;
    begin
      prt('File name: ',1,1);
      if (get_string(filename1,1,12,64)) then
	begin
	  if (length(filename1) = 0) then filename1 := 'MORIAMAP.DAT';
	  open(file1,filename1);
	  if (status(file1) = 0) then
	    begin
	      prt('Writing Moria Dungeon Map...',1,1);
	      put_qio;
	      rewrite(file1);
	      i1 := 1;
	      i7 := 0;
	      repeat
		i2 := 1;
		i3 := i1 + outpage_height - 1;
		if (i3 > cur_height) then
		  i3 := cur_height;
		i7 := i7 + 1;
		i8 := 0;
		repeat
		  i4 := i2 + outpage_width - 1;
		  if (i4 > cur_width) then
		    i4 := cur_width;
		  i8 := i8 + 1;
		  writeln(file1,chr(12));
		  write(file1,'Section[',i7:1,',',i8:1,'];     ',
							error:=continue);
		  writeln(file1,'Depth : ',(dun_level*50):1,' (feet)',
							error:=continue);
		  writeln(file1,' ');
		  write(file1,'   ');
		  for i5 := i2 to i4 do
		    begin
		      i6 := trunc(i5/100);
		      write(file1,i6:1);
		    end;
		  writeln(file1);
		  write(file1,'   ');
		  for i5 := i2 to i4 do
		    begin
		      i6 := trunc(i5/10) - trunc(i5/100)*10;
		      write(file1,i6:1);
		    end;
		  writeln(file1);
		  write(file1,'   ');
		  for i5 := i2 to i4 do
		    begin
		      i6 := i5 - trunc(i5/10)*10;
		      write(file1,i6:1);
		    end;
		  writeln(file1);
		  for i5 := i1 to i3 do
		    begin
		      WriteStr(dun_line,i5:3);
		      for i6 := i2 to i4 do
			begin
			  if (test_light(i5,i6)) then
			    loc_symbol(i5,i6,tmp)
			  else
			    tmp := ' ';
			  dun_line := dun_line + tmp;
			end;
		      writeln(file1,dun_line);
		    end;
		  i2 := i2 + outpage_width;
		until (i2 >= cur_width);
		i1 := i1 + outpage_height;
	      until (i1 >= cur_height);
	      close(file1);
	      prt('Completed.',1,1);
	    end;
	end
    end;


	{ Prints a list of random objects to a file.  Note that -RAK-	}
	{ the objects produced is a sampling of objects which           }
	{ be expected to appear on that level.                          }
procedure print_objects;
    var
	nobj,i1,i2,level                : integer;
	filename1,tmp_str               : string[80];
	file1                           : text;
    begin
      prt('Produce objects on what level?: ',1,1);
      get_string(tmp_str,1,33,10);
      level := 0;
      ReadStr(tmp_str,level);
      prt('Produce how many objects?: ',1,1);
      get_string(tmp_str,1,28,10);
      nobj := 0;
      ReadStr(tmp_str,nobj);
      if ((nobj > 0) and (level > -1) and (level < 1201)) then
	begin
	  if (nobj > 9999) then nobj := 9999;
	  prt('File name: ',1,1);
	  if (get_string(filename1,1,12,64)) then
	    begin
	      if (length(filename1) = 0) then filename1 := 'MORIAOBJ.DAT';
	      open(file1,filename1);
	      if (status(file1) = 0) then
		begin
		  WriteStr(tmp_str,nobj:1);
		  prt(tmp_str + ' random objects being produced...',1,1);
		  put_qio;
		  rewrite(file1);
	writeln(file1,'*** Random Object Sampling:');
	writeln(file1,'*** ',nobj:1,' objects');
	writeln(file1,'*** For Level ',level:1);
	writeln(file1,'');
	writeln(file1,'');
		  popt(i2);
		  for i1 := 1 to nobj do
		    begin
		      t_list[i2] := object_list[get_obj_num(level)];
		      magic_treasure(i2,level);
		      inventory[inven_max] := t_list[i2];
		      with inventory[inven_max] do
			begin
			  unquote(name);
			  known1(name);
			  known2(name);
			end;
		      objdes(tmp_str,inven_max,true);
		      writeln(file1,tmp_str);
		    end;
		  pusht(i2);
		  close(file1);
		  prt('Completed.',1,1);
		end
	      else
		prt('File could not be opened.',1,1);
	    end;
	end;
    end;


	{ Prints a listing of monsters				-RAK-	}
procedure print_monsters;
    var
	i1,i2,xpos,atype,adesc          : integer;
	file1                           : text;
	out_val,filename1               : vtype;
	attstr,attx                     : vtype;
	damstr                          : dtype;

    begin
      prt('File name: ',1,1);
      if (get_string(filename1,1,12,64)) then
	begin
	  if (length(filename1) = 0) then filename1 := 'MORIAMON.DAT';
	  open(file1,filename1);
	  if (status(file1) = 0) then
	    begin
	      prt('Writing Monster Dictionary...',1,1);
	      put_qio;
	      rewrite(file1);
	      for i1 := 1 to max_creatures do
		with c_list[i1] do
		  begin
	{ Begin writing to file                                 }
writeln(file1,'--------------------------------------------');
out_val := name + '                              ';
writeln(file1,i1:3,'  ',out_val:30,'     (',cchar:1,')');
writeln(file1,'     Speed =',speed:2,'  Level     =',level:2,'  Exp =',mexp:5,
							error:=continue);
writeln(file1,'     AC    =',ac:2,   '  Eye-sight =',aaf:2,'  HD  =',hd:5,
							error:=continue);
if (uand($80000000,cmove) <> 0) then
  writeln(file1,'     Creature is a ***Win Creature***');
if (uand($00080000,cmove) <> 0) then
  writeln(file1,'     Creature Eats/kills other creatures.');
if (uand($0001,cdefense) <> 0) then
  writeln(file1,'     Creature is a dragon.');
if (uand($0002,cdefense) <> 0) then
  writeln(file1,'     Creature is a monster.');
if (uand($0004,cdefense) <> 0) then
  writeln(file1,'     Creature is evil.');
if (uand($0008,cdefense) <> 0) then
  writeln(file1,'     Creature is undead.');
if (uand($0010,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by cold.');
if (uand($0020,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by fire.');
if (uand($0040,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by poison.');
if (uand($0080,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by acid.');
if (uand($0100,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by blue light.');
if (uand($0200,cdefense) <> 0) then
  writeln(file1,'     Creature harmed by Stone-to-Mud.');
if (uand($1000,cdefense) <> 0) then
  writeln(file1,'     Creature cannot be charmed or slept.');
if (uand($2000,cdefense) <> 0) then
  writeln(file1,'     Creature seen with Infra-Vision.');
if (uand($4000,cdefense) <> 0) then
  writeln(file1,'     Creature has MAX hit points.');
if (uand($00010000,cmove) <> 0) then
  writeln(file1,'     Creature is invisible.');
if (uand($00100000,cmove) <> 0) then
  writeln(file1,'     Creature picks up objects.');
if (uand($00200000,cmove) <> 0) then
  writeln(file1,'     Creature multiplies.');
if (uand($01000000,cmove) <> 0) then
  writeln(file1,'     Carries object(s).');
if (uand($02000000,cmove) <> 0) then
  writeln(file1,'     Carries gold, gems, ect.');
if (uand($04000000,cmove) <> 0) then
  writeln(file1,'       Has object/gold 60% of time.');
if (uand($08000000,cmove) <> 0) then
  writeln(file1,'       Has object/gold 90% of time.');
if (uand($10000000,cmove) <> 0) then
  writeln(file1,'       Has 1d2 object(s)/gold.');
if (uand($20000000,cmove) <> 0) then
  writeln(file1,'       Has 2d2 object(s)/gold.');
if (uand($40000000,cmove) <> 0) then
  writeln(file1,'       Has 4d2 object(s)/gold.');
	{ Creature casts spells / Breaths Dragon breath...      }
if (spells > 0) then
  begin
    writeln(file1,'   --Spells/Dragon Breath =');
    writeln(file1,'       Casts spells 1 out of ',uand($F,spells):1,
		' turns.');
    if (uand($00000010,spells) <> 0) then
      writeln(file1,'       Can teleport short.');
    if (uand($00000020,spells) <> 0) then
      writeln(file1,'       Can teleport long.');
    if (uand($00000040,spells) <> 0) then
      writeln(file1,'       Teleport player to itself.');
    if (uand($00000080,spells) <> 0) then
      writeln(file1,'       Cause light wounds.');
    if (uand($00000100,spells) <> 0) then
      writeln(file1,'       Cause serious wounds.');
    if (uand($00000200,spells) <> 0) then
      writeln(file1,'       Hold person.');
    if (uand($00000400,spells) <> 0) then
      writeln(file1,'       Cause blindness.');
    if (uand($00000800,spells) <> 0) then
      writeln(file1,'       Cause confusion.');
    if (uand($00001000,spells) <> 0) then
      writeln(file1,'       Cause fear.');
    if (uand($00002000,spells) <> 0) then
      writeln(file1,'       Summon a monster.');
    if (uand($00004000,spells) <> 0) then
      writeln(file1,'       Summon an undead.');
    if (uand($00008000,spells) <> 0) then
      writeln(file1,'       Slow person.');
    if (uand($00010000,spells) <> 0) then
      writeln(file1,'       Drains mana for healing.');
    if (uand($00020000,spells) <> 0) then
      writeln(file1,'       **Unknown spell value**');
    if (uand($00040000,spells) <> 0) then
      writeln(file1,'       **Unknown spell value**');
    if (uand($00080000,spells) <> 0) then
      writeln(file1,'       Breaths Lightning Dragon Breath.');
    if (uand($00100000,spells) <> 0) then
      writeln(file1,'       Breaths Gas Dragon Breath.');
    if (uand($00200000,spells) <> 0) then
      writeln(file1,'       Breaths Acid Dragon Breath.');
    if (uand($00400000,spells) <> 0) then
      writeln(file1,'       Breaths Frost Dragon Breath.');
    if (uand($00800000,spells) <> 0) then
      writeln(file1,'       Breaths Fire Dragon Breath.');
  end;
	{ Movement for creature                                 }
writeln(file1,'   --Movement =');
if (uand($00000001,cmove) <> 0) then
  writeln(file1,'       Move only to attack.');
if (uand($00000002,cmove) <> 0) then
  writeln(file1,'       Move and attack normally.');
if (uand($00000008,cmove) <> 0) then
  writeln(file1,'       20% random movement.');
if (uand($00000010,cmove) <> 0) then
  writeln(file1,'       40% random movement.');
if (uand($00000020,cmove) <> 0) then
  writeln(file1,'       75% random movement.');
if (uand($00020000,cmove) <> 0) then
  writeln(file1,'       Can open doors.');
if (uand($00040000,cmove) <> 0) then
  writeln(file1,'       Can phase through walls.');
writeln(file1,'   --Creature attacks =');
attstr := damage;
while (length(attstr) > 0) do
  begin
    xpos := index(attstr,'|');
    if (xpos > 0) then
      begin
	attx := substr(attstr,1,xpos-1);
	attstr := substr(attstr,xpos+1,length(attstr)-xpos);
      end
    else
      begin
	attx := attstr;
	attstr := '';
      end;
    ReadStr(attx,atype,adesc,damstr);
    out_val := '';
    case adesc of
	1 :  out_val := '       Hits for ';
	2 :  out_val := '       Bites for ';
	3 :  out_val := '       Claws for ';
	4 :  out_val := '       Stings for ';
	5 :  out_val := '       Touches for ';
	6 :  out_val := '       Kicks for ';
	7 :  out_val := '       Gazes for ';
	8 :  out_val := '       Breathes for ';
	9 :  out_val := '       Spits for ';
	10:  out_val := '       Wails for ';
	11:  out_val := '       Embraces for ';
	12:  out_val := '       Crawls on you for ';
	13:  out_val := '       Shoots spores for ';
	14:  out_val := '       Begs for money for ';
	15:  out_val := '       Slimes you for ';
	16:  out_val := '       Crushes you for ';
	17:  out_val := '       Tramples you for ';
	99:  out_val := '       Is repelled...';
	else out_val := '     **Unknown value** ';
    end;
    case atype of
{Normal attack  }     1  : out_val := out_val + 'normal damage.';
{Poison Strength}     2  : out_val := out_val + 'lowering strength.';
{Confusion attack}    3  : out_val := out_val + 'confusion.';
{Fear attack    }     4  : out_val := out_val + 'fear.';
{Fire attack    }     5  : out_val := out_val + 'fire damage.';
{Acid attack    }     6  : out_val := out_val + 'acid damage.';
{Cold attack    }     7  : out_val := out_val + 'cold damage.';
{Lightning attack}    8  : out_val := out_val + 'lightning damage.';
{Corrosion attack}    9  : out_val := out_val + 'corrosion damage.';
{Blindness attack}    10 : out_val := out_val + 'blindness.';
{Paralysis attack}    11 : out_val := out_val + 'paralyzation.';
{Steal Money    }     12 : out_val := out_val + 'stealing money.';
{Steal Object   }     13 : out_val := out_val + 'stealing object.';
{Poison         }     14 : out_val := out_val + 'poison damage.';
{Lose Dex       }     15 : out_val := out_val + 'lose dexterity.';
{Lose Con       }     16 : out_val := out_val + 'lose constitution.';
{Lose Int       }     17 : out_val := out_val + 'lose intelligence.';
{Lose Wis       }     18 : out_val := out_val + 'lose wisdom.';
{Lose Exp       }     19 : out_val := out_val + 'lose experience.';
{Aggravation    }     20 : out_val := out_val + 'aggravates monsters.';
{Disenchant     }     21 : out_val := out_val + 'disenchants objects.';
{Eats food      }     22 : out_val := out_val + 'eating food.';
{Eats light     }     23 : out_val := out_val + 'eating light source.';
{Eats charges   }     24 : out_val := out_val + 'absorbing charges.';
{ Special       }     99 : out_val := out_val + 'blank message.';
		      else out_val := out_val + '**Unknown value**';
    end;
    out_val := out_val + ' (' + damstr + ')';
    writeln(file1,out_val);
  end;
  for i2 := 1 to 2 do writeln(file1,' ');
end;
	{ End writing to file                                   }
	      close(file1);
	      prt('Completed.',1,1);
	    end;
	end
    end;


	{ Print the character to a file or device		-RAK-	}
procedure file_character;
    var
	i1,i2,xbth,xbthb,xfos,xsrh,xstl,xdis            : integer;
	xsave,xdev                                      : integer;
	xinfra                                          : vtype;
	file1                                           : text;
	out_val,filename1,prt1,prt2,new_page            : vtype;
	out_str,out_int,out_wis,out_dex,out_con,out_chr : stat_type;

    begin
      prt('File name: ',1,1);
      if (get_string(filename1,1,12,64)) then
	begin
	  if (length(filename1) = 0) then filename1 := 'MORIACHR.DAT';
	  open(file1,filename1);
	  if (status(file1) = 0) then
	    begin
	      prt('Writing character sheet...',1,1);
	      put_qio;
	      rewrite(file1);
	      new_page := chr(12);
	      writeln(file1,new_page);
	      cnv_stat(py.stat.cstr,out_str);
	      cnv_stat(py.stat.cint,out_int);
	      cnv_stat(py.stat.cwis,out_wis);
	      cnv_stat(py.stat.cdex,out_dex);
	      cnv_stat(py.stat.ccon,out_con);
	      cnv_stat(py.stat.cchr,out_chr);
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,' ');
write(file1,  '  Name  :',pad(py.misc.name,' ',25));
write(file1,  '  Age         :',py.misc.age:4);
writeln(file1,'     Strength     :',out_str:6);
write(file1,  '  Race  :',pad(py.misc.race,' ',25));
write(file1,  '  Height      :',py.misc.ht:4);
writeln(file1,'     Intelligence :',out_int:6);
write(file1,  '  Sex   :',pad(py.misc.sex,' ',25));
write(file1,  '  Weight      :',py.misc.wt:4);
writeln(file1,'     Wisdom       :',out_wis:6);
write(file1,  '  Class :',pad(py.misc.tclass,' ',25));
write(file1,  '  Social Class:',py.misc.sc:4);
writeln(file1,'     Dexterity    :',out_dex:6);
write(file1,  '  Title :',pad(py.misc.title,' ',25));
write(file1,  '               ','    ');
writeln(file1,'     Constitution :',out_con:6);
write(file1,  '         ',' ':30);
write(file1,  '              ');
writeln(file1,'     Charisma     :',out_chr:6);
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,' ');
write(file1,  '  + To Hit    :',py.misc.dis_th:6);
write(file1,  '     Level      :',py.misc.lev:6);
writeln(file1,'     Max Hit Points :',py.misc.mhp:6);
write(file1,  '  + To Damage :',py.misc.dis_td:6);
write(file1,  '     Experience :',py.misc.exp:6);
writeln(file1,'     Cur Hit Points :',trunc(py.misc.chp):6);
write(file1,  '  + To AC     :',py.misc.dis_tac:6);
write(file1,  '     Gold       :',py.misc.au:6);
writeln(file1,'     Max Mana       :',py.misc.mana:6);
write(file1,  '    Total AC  :',py.misc.dis_ac:6);
write(file1,  '                       ');
writeln(file1,'     Cur Mana       :',py.misc.mana:6);

	      writeln(file1,' ');
	      writeln(file1,' ');
	      with py.misc do
		begin
		  xbth  := bth + lev*bth_lev_adj + ptohit*bth_plus_adj;
		  xbthb := bthb + lev*bth_lev_adj + ptohit*bth_plus_adj;
		  xfos  := 27 - fos;
		  if (xfos < 0) then xfos := 0;
		  xsrh  := srh + int_adj;
		  xstl  := stl;
		  xdis  := disarm + lev + 2*todis_adj + int_adj;
		  xsave := save + lev + wis_adj;
		  xdev := save + lev + int_adj;
		  WriteStr(xinfra,py.flags.see_infra*10:1,' feet');
		end;
writeln(file1,'(Miscellaneous Abilities)':40);
writeln(file1,' ');
write(file1,  '  Fighting    : ',pad(likert(xbth ,12),' ',10));
write(file1,  '  Stealth     : ',pad(likert(xstl , 1),' ',10));
writeln(file1,'  Perception  : ',pad(likert(xfos , 3),' ',10));
write(file1,  '  Throw/Bows  : ',pad(likert(xbthb,12),' ',10));
write(file1,  '  Disarming   : ',pad(likert(xdis , 8),' ',10));
writeln(file1,'  Searching   : ',pad(likert(xsrh , 6),' ',10));
write(file1,  '  Saving Throw: ',pad(likert(xsave, 6),' ',10));
write(file1,  '  Magic Device: ',pad(likert(xdev , 7),' ',10));
writeln(file1,'  Infra-Vision: ',pad(xinfra,' ',10));
	{ Write out the character's history     }
writeln(file1,' ');
writeln(file1,' ');
writeln(file1,'Character Background':45);
for i1 := 1 to 5 do writeln(file1,pad(py.misc.history[i1],' ',71):76);
	{ Write out the equipment list...       }
	      i2 := 0;
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,'  [Character''s Equipment List]');
	      writeln(file1,' ');
if (equip_ctr = 0) then
  writeln(file1,'  Character has no equipment in use.')
else
  for i1 := 23 to inven_max-1 do
    with inventory[i1] do
      if (tval > 0) then
	begin
	  case i1 of
	    23 :        prt1 := ') You are wielding   : ';
	    24 :        prt1 := ') Worn on head       : ';
	    25 :        prt1 := ') Worn around neck   : ';
	    26 :        prt1 := ') Worn on body       : ';
	    27 :        prt1 := ') Worn on shield arm : ';
	    28 :        prt1 := ') Worn on hands      : ';
	    29 :        prt1 := ') Right ring finger  : ';
	    30 :        prt1 := ') Left  ring finger  : ';
	    31 :        prt1 := ') Worn on feet       : ';
	    32 :        prt1 := ') Worn about body    : ';
	    33 :        prt1 := ') Light source is    : ';
	    34 :        prt1 := ') Secondary weapon   : ';
	    else   prt1 := ') *Unknown value*    : ';
	  end;
	  i2 := i2 + 1;
	  objdes(prt2,i1,true);
	  WriteStr(out_val,'  ',chr(i2+96),prt1,prt2);
	  writeln(file1,out_val);
	end;
	{ Write out the character's inventory...        }
	      writeln(file1,new_page);
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,' ');
	      writeln(file1,'  [General Inventory List]');
	      writeln(file1,' ');
if (inven_ctr = 0) then
  writeln(file1,'  Character has no objects in inventory.')
else
  begin
    for i1 := 1 to inven_ctr do
      begin
	objdes(prt1,i1,true);
	WriteStr(out_val,chr(i1+96),') ',prt1);
	writeln(file1,out_val);
      end
  end;
	      writeln(file1,new_page);
	      close(file1);
	      prt('Completed.',1,1);
	    end;
	end
    end;
