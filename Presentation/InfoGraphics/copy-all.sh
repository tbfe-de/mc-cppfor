#!/bin/bash
# -----------------------------------------------------------------------------
# Copy PNG-Files for all Info-Graphics here
# -----------------------------------------------------------------------------

# Set this to the storing of PNG Files
#
InfoGraphics_PNG=../../../../InfoGraphics/PNG

# List all the files (order may matter some day -- not yet now)
cat <<-+++ |
	:::::::::::::::::::::::::::: Intro
	TestBrowserNavigation

	:::::::::::::::::::::::::::: Monday 1
	StringBasics
	IOStreamBasics
	ParametrizedTypesAndSizes

	:::::::::::::::::::::::::::: Monday 2 
	ExecutionModel
	ClassToMemoryMapping
	ContainerImplementations
	RuntimeTypeIdentification
	TypeBasedBranching

	:::::::::::::::::::::::::::: Tuesday 1
	UML-ClassesAndRelations 
	MultipleInheritance
	DiamondShapedInheritance
	Example-ClassDesign

	:::::::::::::::::::::::::::: Tuesday 2
	STL-SequenceContainers
	STL-ContainerIterators
	STL-IteratorDetails
	STL-AssociativeContainers

	:::::::::::::::::::::::::::: Wednesday 1
	STL-IteratorCategories
	STL-IteratorUsages

	:::::::::::::::::::::::::::: Wednesday 2
	TemplateBasics
	ReducingCodeBloat

	:::::::::::::::::::::::::::: Thursday 1
	GuidingPrinciples
	Example-OpenClosePrinciple

	:::::::::::::::::::::::::::: Thursday 2
	ExceptionBasics
	ExceptionDetails

	:::::::::::::::::::::::::::: Friday 1
	ResourceManagement
	SmartPointers
+++
sed '/^[ 	]*$/d' | (
	while read word line
	do
		case $word in
		(\#)	# comment ignored
			continue;;
		(:*)	test -n "$notfirst" && echo
			notfirst=notfirst
			echo -n "$line "
			continue;;
		(*[\ \	]*)
			>&2 echo "$0: invalid line ignored: $line"
			continue;;
		(*)	file="$word.png"
			src="$InfoGraphics_PNG/$file"
		esac
		test -f "$src" || {
			>&2 echo "$0: no such file: $src"
			continue
		}
		test "$src" -nt "$file" && {
			cp -a "$src" "$file"
			echo -n "."
		}
	done
	test -n "$notfirst" && echo
)

