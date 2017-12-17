/* 
	the format of the tree definition file is simple,
	you can find specification in the Tigra Menu documentation at:
	
	http://www.softcomplex.com/products/tigra_tree_menu/docs/index.html#hierarchy
*/

var TREE_ITEMS = 
[
	['Oracle SQL Developer Tutorial','html/tutorialhome.htm', 
	   ['Using this Tutorial','html/tutorialhome_p2.htm',
		  ['Tutorial Scenario','html/tutorialhome_p3.htm',
            ]
		],
		['Product Overview','html/productovw.htm',
          ],
        ['Installation','html/module1/mod01_sm_install.htm'
          ],  		
        ['What to Do First','html/module2/mod02_wli_crdbconn.htm',
		   ['Creating a Database Connection','html/module2/mod02_sm_crdbconn.htm'
             ]
		 ],
        ['Working with Database Objects','html/module3/mod03_wli_dbobj.htm',
            ['Creating Tables','html/module3/mod03_tm_cretab.htm',
                ['Creating Tables Using the Table Dialog','html/module3/mod03_sm_cretab01.htm'
                ],
				['Creating Tables Using SQL','html/module3/mod03_sm_cretab02.htm'
                ],
				['Creating a Copy of a Table','html/module3/mod03_sm_cretab03.htm'
                ]
			 ],
            ['Modifying Tables','html/module3/mod03_tm_modtab.htm',
                ['Adding a New Column','html/module3/mod03_sm_modtab.htm'
                ]
			 ],
		    ['Managing Constraints','html/module3/mod03_tm_mancon01.htm',
				['Identifying Constraints','html/module3/mod03_tm_mancon02.htm',
                ],
				['Creating Constraints','html/module3/mod03_tm_mancon03.htm',
				   ['Implementing Business Rules','html/module3/mod03_sm_mancon.htm'
                    ]
				],
				['Reviewing Constraint Information','html/module3/mod03_sm_viewcon.htm'
                 ] 
			 ],
			['Removing Tables','html/module3/mod03_tm_remtab.htm',
                ['Removing a Table','html/module3/mod03_sm_remtab.htm'
                ]
			 ]
		 ],
		['Accessing Data','html/module4/mod04_wli_accessdata.htm',
            ['Building Simple Queries','html/module4/mod04_tm_writeq.htm',
                ['Retrieving Columns','html/module4/mod04_sm_retrievecol.htm'
                ],
                ['Retrieving Rows','html/module4/mod04_sm_retrieverows.htm'
                ],
                ['Using the Query Builder','html/module4/mod04_sm_qrybldr.htm'
                ]
			 ],
            ['Accessing Multiple Tables','html/module4/mod04_wli_joiningtbl.htm',
                ['Understanding Simple Joins','html/module4/mod04_tm_simplejoin.htm',
				   ['Creating a Simple Join Query','html/module4/mod04_sm_simplejoin.htm'
                   ]
                ],
                ['Joining Tables and Identifying Columns','html/module4/mod04_tm_onclause.htm',
				   ['Writing a Query that uses the ON Clause','html/module4/mod04_sm_onclause.htm'
                   ]
                ],
                ['Applying Additional Conditions to a Join','html/module4/mod04_tm_whereclause.htm',
				   ['Writing a Query that uses the WHERE Clause','html/module4/mod04_sm_whereclause.htm'
                   ]
				],
                ['Joining Multiple Tables','html/module4/mod04_tm_multijoin.htm',
				   ['Writing a Query that Joins Multiple Tables','html/module4/mod04_sm_multijoin.htm'
                   ]
				]
			 ],
            ['Using Functions to Customize Output','html/module4/mod04_wli_functions.htm',
                ['Character Functions','html/module4/mod04_tm_funcchar.htm',
				   ['Using Character Functions','html/module4/mod04_sm_funcchar.htm'
                   ]
                ],
                ['Numeric Functions','html/module4/mod04_tm_funcnum.htm',
				   ['Using Numeric Functions','html/module4/mod04_sm_funcnum.htm'
                   ]
                ],
                ['Date Functions','html/module4/mod04_tm_funcdate.htm',
				   ['Using Date Functions','html/module4/mod04_sm_funcdate.htm'
                   ],
				   ['Formatting Dates','html/module4/mod04_tm_funcdateformat.htm',
				     ['Manipulating Dates','html/module4/mod04_sm_funcdateformat.htm'
                     ]
				   ]
                ],
                ['The NVL Function','html/module4/mod04_tm_funcnvl.htm',
				   ['Using the NVL Function','html/module4/mod04_sm_funcnvl.htm'
                   ]
                ]
			 ],
            ['Working With Groups of Data','html/module4/mod04_wli_groups.htm',
                ['Group Functions','html/module4/mod04_tm_grpfunc.htm',
				   ['Using Group Functions','html/module4/mod04_sm_grpfunc.htm'
                   ]
				],
                ['Creating Groups','html/module4/mod04_tm_grpcreate.htm',
				   ['Building Reports of Grouped Data','html/module4/mod04_sm_grpcreate.htm'
                   ]
				],
                ['Restricting Groups','html/module4/mod04_tm_grprestrict.htm',
				   ['Using the HAVING Clause','html/module4/mod04_sm_grprestrict.htm'
                   ]
                ]
			 ],
		 ],
		['Manipulating Data','html/module5/mod05_wli_mandata.htm',
            ['Adding Data','html/module5/mod05_tm_adddata.htm',
                ['Inserting One Row','html/module5/mod05_sm_insertrow.htm'
                ],
				['Inserting Multiple Rows','html/module5/mod05_sm_insertmultirow.htm'
				 ]
			 ],
            ['Modifying Data','html/module5/mod05_tm_updatedata.htm',
                ['Updating a Row','html/module5/mod05_sm_updaterow.htm'
                ],
				['Updating Multiple Rows Using SQL','html/module5/mod05_sm_updatemultirow.htm'
                ],
				['Updating a CLOB Value','html/module5/mod05_sm_updateclob.htm'
                ]
			 ],
		    ['Removing Data','html/module5/mod05_tm_deletedata.htm',
                ['Deleting a Row','html/module5/mod05_sm_deleterow.htm'
                ]
			 ],
			['Saving and Discarding Changes','html/module5/mod05_tm_savchgs.htm',
                ['Committing and Rolling Back Changes','html/module5/mod05_sm_savchgs.htm'
                ]
			 ],
			['Exporting Data','html/module5/mod05_tm_exportdata.htm',
                ['Exporting Data to MS Excel Format','html/module5/mod05_sm_exportdata.htm'
                ],
				['Exporting DDL','html/module5/mod05_sm_exportddl.htm'
                ]
			 ],
			['Importing Data','html/module5/mod05_tm_importdata.htm',
                ['Importing Data From a Spreadsheet','html/module5/mod05_sm_impdata.htm'
                ]
			 ]
		 ],
		['Adding PL/SQL Components','html/module8/mod08_wli_plsql.htm',
		 	['PL/SQL Blocks','html/module8/mod08_tm_block.htm',
			   ['Creating an Anonymous Block','html/module8/mod08_sm_crblock.htm'
			    ]
			 ],
			['Using Triggers','html/module8/mod08_wli_triggers.htm',
				['DML Triggers','html/module8/mod08_tm_dmltriggers.htm',
    			   ['Creating a DML Trigger','html/module8/mod08_sm_dmltrigger.htm'
			        ]
            	 ],
				['Managing Triggers','html/module8/mod08_tm_mngtriggers.htm'
            	 ],
				['Auditing the Data','html/module8/mod08_tm_audittriggers.htm',
    			   ['Creating a Trigger for Auditing','html/module8/mod08_sm_audittrigger.htm'
			        ]
            	 ]
	         ],	
			['Using Procedures and Functions','html/module8/mod08_wli_procfunc.htm',
				['Creating Procedures','html/module8/mod08_tm_crproc.htm',
				  ['Using Parameters','html/module8/mod08_tm_proc_parms.htm'
            	   ],
				  ['Creating a Procedure','html/module8/mod08_sm_proc_create.htm'
            	   ]
				],
				['Creating Functions','html/module8/mod08_tm_crfunc.htm',
				  ['Creating Functions: An Example','html/module8/mod08_tm_crfunc2.htm'
            	   ],
				  ['Creating a Function','html/module8/mod08_sm_func_create.htm'
            	   ]
            	 ],
				['Handling Exceptions','html/module8/mod08_tm_except.htm',
				  ['Handling Exceptions: An Example','html/module8/mod08_tm_except2.htm'
            	   ],
				  ['Adding Exceptions','html/module8/mod08_sm_except.htm'
            	   ]
				 ],
				['Debugging PL/SQL','html/module8/mod08_tm_debugger.htm',
				  ['Debugging a Procedure','html/module8/mod08_sm_debugger.htm'
            	   ]
            	 ],
				['Profiling PL/SQL','html/module8/mod08_tm_profiler.htm',
				  ['Profiling a Procedure','html/module8/mod08_sm_profiler.htm'
            	   ]
            	 ]
	         ],	
			['Using Packages','html/module8/mod08_wli_pkg.htm',
				['Creating the Package Specification','html/module8/mod08_tm_pkgspec.htm'
            	 ],
				['Creating the Package Body','html/module8/mod08_tm_pkgbody.htm'
            	 ],
				['Implementing a Package','html/module8/mod08_sm_implpkg.htm'
            	 ]
	         ]
		],
	   ['Building Reports','html/module9/mod09_wli_reports.htm',
			['Producing a User Defined Report','html/module9/mod09_sm_udrpt.htm'
             ]
	    ],
	   ['Using Source Code Control','html/module9/mod09_wli_scc.htm',
			['Versioning Files','html/module9/mod09_sm_versioning.htm'
             ]
	    ],
  	['Additional Learning Resources','html/adlearnresource.htm'
  	 ],
	['Definitions','html/general/definitions.htm'
  	],
	['Summary','html/tutorialsummary.htm'
  	]
   ]
];