#!/usr/bin/perl
use strict;
use warnings;

#Contains all scanned targets in the format "Filename" => {scanned => 0, compiled => 0, uncompiledDeps => 0, referencingFiles => ()}
my $targets = {};
my @unscanned = ();

sub setupTarget {
  my $targetname = shift;

  return if defined($targets->{$targetname});

  my $newEntry = {
    scanned => 0,
    compiled => 0,
    uncompiledDeps => 0,
    referencingFiles => [],
  };

  $targets->{$targetname} = $newEntry;
}

sub hasBeenScanned {
  my $targetname = shift;
  return 0 unless defined($targets->{$targetname});

  return $targets->{$targetname}->{"scanned"} or 0;
}
sub markAsScanned {
  my $targetname = shift;
  $targets->{$targetname}->{"scanned"} = 1;
}
sub addReferencingFile {
  my ($targetname, $filename) = @_;
  push $targets->{$targetname}->{"referencingFiles"}, $filename;
}

sub getSourceFile {
  my $fName = shift;
  $fName =~ s/\.(h|hpp)//;

  return ($fName . ".c") if( -f ($fName . ".c"));
  return ($fName . ".cpp") if( -f ($fName . ".cpp"));
  return 0;
}

sub getFileDir {
  my $fName = shift;
  $fName =~ s/\/[\w\.]*$/\//;
  return $fName;
}

sub cleanFileDir {
  my $fName = shift;
  while($fName =~ /[\w]+\/\.\.\//) {
    $fName =~ s/[\w]+\/\.\.\///;
  }
  return $fName;
}

sub scanFile {
  my $scanFilename = shift;
  $scanFilename = cleanFileDir($scanFilename);

  my $scanFiledir = getFileDir($scanFilename);

  return 0 if hasBeenScanned($scanFilename);

  open(my $to_scan_file, "<", $scanFilename) or return 0;

  print "Scanning $scanFilename\n";

  while(<$to_scan_file>) {
    # Filter out any lines containing a possible #include "NAME.h"
    if($_ =~ /#include\s*"([\w\/(\.\.)]+\.(?:h|hpp))"/) {
      my $includedFile = $scanFiledir . $1;
      $includedFile = cleanFileDir($includedFile);

      my $sourcefile = getSourceFile($includedFile);

      next if $sourcefile eq $scanFilename;

      if($sourcefile) {
        print " - $sourcefile\n";

        $targets->{$scanFilename}->{"uncompiledDeps"}++;

        setupTarget($sourcefile);
        addReferencingFile($sourcefile, $scanFilename);

        push @unscanned, $sourcefile if not hasBeenScanned($sourcefile);
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
    print "Detected File: $_\n";
    print " Dependencies: $targets->{$_}->{'uncompiledDeps'}\n";
  }
}

scanAllFiles("../MainBoard/main.cpp");
printAllFiles();
