#!/usr/bin/perl

use strict;
use warnings;

package CScan;

use vars qw($VERSION @ISA @EXPORT);
require Exporter;
@ISA = qw(Exporter);
our @EXPORT_OK = qw();

# Filename-Based operations (getting directory and cleaning)
sub clean_file_dir {
	my $fname = shift;

	return $fname unless $fname =~ /\.\./;

	while($fname =~ /[\w]+\/\.\.\//) {
		$fname =~ s/[\w]+\/\.\.\///;
	}
	return $fname;
}

sub cut_filename {
	my $fname = shift;
	$fname =~ s/\/[\w\.]*$/\//;
	return clean_file_dir($fname);
}

sub get_sourcefile {
	my $fname = clean_file_dir(shift);

	$fname =~ s/\.(h|hpp)//;

	return ($fname . ".c") if( -f ($fname . ".c"));
	return ($fname . ".cpp") if( -f ($fname . ".cpp"));
	return 0;
}

######################

sub new_filetree {
	my $ftree = {};
	return $ftree;
}

sub fileentry_exists {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	return defined($ftree->{$fname});
}

sub add_file {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	return if fileentry_exists($ftree, $fname);

	my $newEntry = {
		scanned => 0,
	 };

	$ftree->{$fname} = $newEntry;
}

sub mark_scanned {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	return 0 unless fileentry_exists($ftree, $fname);

	$ftree->{$fname}->{"scanned"} = time();
}

sub get_scanned {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	return 0 unless fileentry_exists($ftree, $fname);

	return $ftree->{$fname}->{"scanned"};
}

sub needs_rescan {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	return 0 unless fileentry_exists($ftree, $fname);

	return ((stat($fname))[9] > get_scanned($ftree, $fname));
}

sub get_included_files {
	my $fname = shift;
	my $file_dir = cut_filename($fname);

	open(my $fhandle, "<", $fname) or die "File $fname could not be opened for include scanning!";

	my @included_files = ();

	while(<$fhandle>) {
		if($_ =~ /#include\s*"([\w\/(\.\.)]+\.(?:h|hpp))"/) {
			push(@included_files, clean_file_dir($file_dir . $1));
		}
	}

	return @included_files;
}

sub scan_file {
	my ($ftree, $fname) = @_;
	$fname = clean_file_dir($fname);

	add_file($ftree, $fname);

	return 2 unless needs_rescan($ftree, $fname);

	my @included_files = get_included_files($fname);

	for(@included_files) {
		add_file($ftree, $_);

		my $sFile = get_sourcefile($_);
		add_file($ftree, $sFile) if($sFile);
	}

	mark_scanned($ftree, $fname);

	return 1;
}

sub rescan_all {
	my ($ftree) = @_;

	my $unscanned_remaining = 1;

	while($unscanned_remaining) {
		$unscanned_remaining = 0;

		for(keys($ftree)) {
			$unscanned_remaining = 1 if (scan_file($ftree, $_) == 1);
		}
	}
}

sub get_all_files {
	my ($ftree) = @_;
	my @files = ();

	push(@files, $_) for(keys($ftree));

	return @files;
}

sub get_all_sourcefiles {
	my ($ftree) = @_;
	my @files = ();

	for(keys($ftree)) {
		push(@files, $_) if($_ =~ /.*(\.cpp|\.c)/);
	}

	return @files;
}

my $ftree = new_filetree();
add_file($ftree, "/home/xasin/XasWorks/LZRTag/EclipseWS/MainBoard/Localcode/Connector.h");
rescan_all($ftree);

print $_ . "\n" for(get_all_sourcefiles($ftree));

1;
