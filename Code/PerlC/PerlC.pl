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
	my $fullFilename = $workEnv->{path} . $scanFilename;

	open(my $to_scan_file, "<", $fullFilename) or return 0;

	while(<$to_scan_file>) {
		# Filter out any lines containing a possible #include "NAME.h"
		if($_ =~ /#include\s*"([\w\-\/(\.\.)]+\.(?:h|hpp))"/) {
			my $includedFile = FNameOps::cleanPath($scanFiledir . $1);

			markToScan $workEnv, $includedFile;

			my $sourcefile = FNameOps::getMatching($workEnv->{path} . $includedFile, "c", "cpp");
			$sourcefile =~ s/^$workEnv->{path}//;

			if($sourcefile) {
				markToScan $workEnv, $sourcefile;
				Filetree::addFile $workEnv->{files}, $sourcefile;
			}
		}
	}

	markAsScanned $workEnv, $scanFilename;
	close $to_scan_file;
}

sub scanAllFiles {
	my $workEnv = shift;

	# Explicitly use an array dereference, otherwise the loop turns endless :c
	while(@{$workEnv->{unscanned}}) {
		my $nextFile = pop $workEnv->{unscanned};

		scanFile($workEnv, $nextFile);
	}
}

sub addStartFile {
	my $workEnv = shift;
	my $fName = shift;

	Filetree::addFile $workEnv->{files}, $fName;
	push $workEnv->{unscanned}, $fName;
}

sub setupScan {
	my $workEnv = shift;

	$workEnv->{files} = {} unless defined $workEnv->{files};
	$workEnv->{unscanned} = [] unless defined $workEnv->{unscanned};
	$workEnv->{scanned} = {} unless defined $workEnv->{scanned};

	die "No start files were specified!" unless defined $workEnv->{startFiles};

	foreach(@{$workEnv->{startFiles}}) {
		addStartFile $workEnv, $_;
	}
}


print "Running PerlC on file: " . $ARGV[0] . "\n";

my $workingEnv = do($ARGV[0]);
$workingEnv->{path} = FNameOps::getPath($ARGV[0]);
print "Working environment: " . $workingEnv->{path} ."\n";

setupScan $workingEnv;
scanAllFiles $workingEnv;

foreach(keys $workingEnv->{files}) {
	print $_ . "\n";
}
