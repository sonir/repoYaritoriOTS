{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 3,
			"revision" : 4,
			"architecture" : "x86",
			"modernui" : 1
		}
,
		"rect" : [ 34.0, 79.0, 772.0, 887.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "signal", "list", "list" ],
					"patching_rect" : [ 44.0, 271.0, 85.0, 22.0 ],
					"style" : "",
					"text" : "omx.peaklim~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 44.0, 194.0, 212.0, 48.0 ],
					"presentation_rect" : [ 0.0, 0.0, 50.0, 34.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~",
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 44.0, 345.0, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"data" : 					{
						"clips" : [ 							{
								"filename" : "/Users/rin/Desktop/180114_cmma/stable/_sliceBuf/soundproto_origin.wav",
								"filekind" : "audiofile",
								"loop" : 0,
								"content_state" : 								{
									"slurtime" : [ 0.0 ],
									"followglobaltempo" : [ 0 ],
									"pitchcorrection" : [ 0 ],
									"play" : [ 0 ],
									"speed" : [ 1.0 ],
									"quality" : [ "basic" ],
									"originallength" : [ 0.0, "ticks" ],
									"mode" : [ "basic" ],
									"timestretch" : [ 0 ],
									"formantcorrection" : [ 0 ],
									"originaltempo" : [ 120.0 ],
									"basictuning" : [ 440 ],
									"formant" : [ 1.0 ],
									"pitchshift" : [ 1.0 ],
									"originallengthms" : [ 0.0 ]
								}

							}
 ]
					}
,
					"id" : "obj-11",
					"maxclass" : "playlist~",
					"numinlets" : 1,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "signal", "", "dictionary" ],
					"patching_rect" : [ 44.0, 58.0, 187.0, 31.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 44.0, 137.0, 40.0, 22.0 ],
					"style" : "",
					"text" : "storm"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 1 ],
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 1 ],
					"source" : [ "obj-11", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 1 ],
					"source" : [ "obj-2", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-1::obj-5::obj-10" : [ "DryWet[5]", "DryWet", 0 ],
			"obj-10" : [ "live.gain~", "live.gain~", 0 ],
			"obj-1::obj-4::obj-10" : [ "DryWet", "DryWet", 0 ],
			"obj-1::obj-3::obj-10" : [ "DryWet[3]", "DryWet", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "storm.maxpat",
				"bootpath" : "~/Desktop/180114_cmma/stable/_sliceBuf",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "SimpleDelay_First.maxpat",
				"bootpath" : "~/Desktop/180114_cmma/stable/_sliceBuf",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "drywet.maxpat",
				"bootpath" : "~/Desktop/180114_cmma/stable/_sliceBuf",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "SimpleDelay_Second.maxpat",
				"bootpath" : "~/Desktop/180114_cmma/stable/_sliceBuf",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "soundproto_origin.wav",
				"bootpath" : "~/Desktop/180114_cmma/stable/_sliceBuf",
				"patcherrelativepath" : ".",
				"type" : "WAVE",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
