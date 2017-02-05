#!/usr/bin/perl
use strict;
use warnings;

use FNameOps;

#Contains all scanned targets in the format "Filename" => {scanned => 0, compiled => 0, uncompiledDeps => 0, referencingFiles => ()}
my $targets = {};
my @unscanned = ();
my %scanned = ();

sub setupTarget {
  my $targetname = shift;

  return if defined($targets->{$targetname});

  my $newEntry = {
    referencingFiles => [],
 	};

  $targets->{$targetname} = $newEntry;
}

sub hasBeenScanned {
  my $targetname = shift;
  return defined($scanned{$targetname});
}
sub markAsScanned {
  my $targetname = shift;
  $scanned{$targetname} = 1;
}

sub addReferencingFile {
  my ($targetname, $filename) = @_;
  push $targets->{$targetname}->{"referencingFiles"}, $filename;
}

sub scanFile {
  my $scanFilename = FNameOps::cleanPath shift;
  my $scanFiledir = FNameOps::getPath $scanFilename;

  return 0 if hasBeenScanned($scanFilename);

  open(my $to_scan_file, "<", $scanFilename) or return 0;

  print "Scanning $scanFilename\n";

  while(<$to_scan_file>) {
		# Filter out any lines containing a possible #include "NAME.h"
		if($_ =~ /#include\s*"([\w\-\/(\.\.)]+\.(?:h|hpp))"/) {
			my $includedFile = FNameOps::cleanPath($scanFiledir . $1);
			push @unscanned, $includedFile unless hasBeenScanned($includedFile);

			my $sourcefile = FNameOps::getMatching($includedFile, "c", "cpp");

			if($sourcefile) {
				push @unscanned, $sourcefile unless hasBeenScanned($sourcefile);

				setupTarget($sourcefile);
				addReferencingFile($sourcefile, $scanFilename);
			}
		}
	}

	markAsScanned($scanFilename);
	close $to_scan_file;
}

sub scanAllFiles {
  my $startFile = shift;
  setupTarget($startFile);

  print "Starting to search for all includes, starting from: $startFile\n";

  push(@unscanned, $startFile);

  while(@unscanned) {
    my $nextFile = pop(@unscanned);
    scanFile($nextFile);
  }
}

sub printAllFiles {
	foreach(keys($targets)) {
		print "Detected Source File: $_\n";
	}
}

scanAllFiles("/home/xasin/XasWorks/Notos/EclipseWS/Notos_Main/main.cpp");
print "\n";
printAllFiles();
print("Scanned " . keys(%scanned) . " files alltogether, found " . keys($targets) . " source files!\n");
