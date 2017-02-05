#!/usr/bin/perl
use strict;
use warnings;

use FNameOps;
use Filetree;

sub hasBeenScanned {
	my $workEnv = shift;
	my $targetname = shift;
	return defined($workEnv->{scanned}->{$targetname});
}
sub markAsScanned {
	my $workEnv = shift;
	my $targetname = shift;

	$workEnv->{scanned}->{$targetname} = 1;
}

sub markToScan {
	my $workEnv = shift;
	my $targetname = shift;

	push $workEnv->{unscanned}, $targetname unless hasBeenScanned $workEnv, $targetname;
}

sub scanFile {
	my $workEnv = shift;
 	my $scanFilename = FNameOps::cleanPath shift;
	return if hasBeenScanned $workEnv, $scanFilename;

	my $scanFiledir = FNameOps::getPath $scanFilename;

	open(my $to_scan_file, "<", $scanFilename) or return 0;

	while(<$to_scan_file>) {
		# Filter out any lines containing a possible #include "NAME.h"
		if($_ =~ /#include\s*"([\w\-\/(\.\.)]+\.(?:h|hpp))"/) {
			my $includedFile = FNameOps::cleanPath($scanFiledir . $1);

			markToScan $workEnv, $includedFile;

			my $sourcefile = FNameOps::getMatching($includedFile, "c", "cpp");
			if($sourcefile) {
				markToScan $workEnv, $sourcefile;
				Filetree::addFile $workEnv->{files}, $sourcefile;
			}
		}
	}

	markAsScanned $workEnv, $scanFilename;
	close $to_scan_file;
}

sub scanFilesFrom {
	my $workEnv = shift;
	my $startFile = shift;

	Filetree::addFile $workEnv->{files}, $startFile;

	push $workEnv->{unscanned}, $startFile;

	# Explicitly use an array dereference, otherwise the loop turns endless :c
	while(@{$workEnv->{unscanned}}) {
		my $nextFile = pop $workEnv->{unscanned};

		scanFile($workEnv, $nextFile);
	}
}

sub setupWorkEnv {
	my $workEnv = shift;

	$workEnv->{files} = {} unless defined $workEnv->{files};
	$workEnv->{unscanned} = [] unless defined $workEnv->{unscanned};
	$workEnv->{scanned} = {} unless defined $workEnv->{scanned};
}

my $workingEnv = {};
setupWorkEnv $workingEnv;
scanFilesFrom $workingEnv, "/home/xasin/XasWorks/Notos/EclipseWS/Notos_Main/main.cpp";
foreach(keys $workingEnv->{files}) {
	print $_ . "\n";
}
