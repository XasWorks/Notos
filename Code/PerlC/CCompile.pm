#!/usr/bin/perl

use strict;
use warnings;
use CScan;

package CScan;

my $cOptions = do "ComOps.pl";

sub get_files_from_ftree {
	my ($ftree) = @_;

	return $ftree if ref $ftree eq 'ARRAY';
	return keys($ftree) if ref $ftree eq 'HASH';
}

sub clean_directory {
	my $dir = shift;
	$dir =~ s/[\w\.]*$// if -f $dir;
	$dir =~ s/[\w]+\.[\w]+$//;
	$dir .= '/' unless $dir =~ /\/$/;

	return $dir;
}

## ACTUAL FUNCTIONS

# Recursively generate the directory given.
sub generate_directory_recursion {
	my ($directory) = @_;

	return unless defined $directory and length $directory;
	return if -d $directory;

	my $cutdir = $directory;
	$cutdir =~ s/\w*\/$//;

	generate_directory_recursion($cutdir);

	print($directory . "\n");

	system("mkdir", $directory);
}

# The main interface function. Ensures that the thing doesn't try to make a directory of a file.
sub generate_directory {
	my ($directory) = @_;
	generate_directory_recursion(clean_directory($directory));
}

# Generates the actual files at the position specified by $treeloc, or "." otherwise
sub generate_filetree {
	my ($fdata, $treeloc) = @_;

	$fdata = get_files_from_ftree $fdata;
	$treeloc = "./BIN/" unless defined $treeloc;

	print "Putting the data at $treeloc!\n";

	for(@$fdata) {
		my $cDir = $treeloc . $_;
		$cDir =~ s/\/\//\//;

 		generate_directory($cDir);
	}
}

sub generate_ccommand {
	my ($command, $fname) = @_;

	my $strippedName = $fname;
	$strippedName =~ s/\.\w*$//;

	$cOptions->{"strippedName"} 	= $strippedName;
	$cOptions->{"inputFile"} 		= $fname;

	for(keys($cOptions)) {
		my ($key, $replacement) = ($_, $cOptions->{$_});
		$command =~ s/$key/$replacement/;
	}

	print $command . "\n";
}

sub test_functions {
	my $testFiletree = CScan::new_filetree();
	CScan::add_file($testFiletree, "/home/xasin/XasWorks/LZRTag/EclipseWS/MainBoard/main.cpp");
	CScan::rescan_all($testFiletree);

	my @sfiles = CScan::get_all_sourcefiles($testFiletree);
	generate_filetree(\@sfiles);
	print "\n";
}

generate_ccommand("avr-gcc -DF_CPU=Frequency -mmcu=Chip -Wall -c -o strippedName.o -OOptimisation inputFile", "main.c");
