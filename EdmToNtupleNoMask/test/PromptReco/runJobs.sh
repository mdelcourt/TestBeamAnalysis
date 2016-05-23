#!/bin/bash

#for i in `echo `
#last run 569
#for i in $(seq 554 569)
#for i in `echo 574 575 576 578 579 583 582 584 585 586 587 588 590 591 592 593 594 595`
#for i in ` echo 597 598 599 600 601 603 605 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 628 629 630 631 632 633 634 635 636 637 638 639 640 642 643 644 645 646 647 648 649 650 651 652 656 655 657 658 659 660 661 662 663 644 665 666 667 668 669 671 672 673 674 675 676 678 679 `
#for i in ` echo 685 686 689 688 690 691 692 693 684 695 696 698 699 701 702 703 704 706 707 708 `
#for i in ` echo 706 707 708 711 713 714 715 716 720 718 719 721 722 724 725 726 `
for i in ` echo 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 `
do 
  echo $i
  cmsRun scripts/treeMaker_cfg.py "/afs/cern.ch/user/s/sroychow/public/sinpStorage/sroychow/May2016BeamTest/EDM/USC.00000"$i".0001.A.storageManager.00.0000.root" "/afs/cern.ch/user/s/sroychow/public/sinpStorage/sroychow/May2016BeamTest/Ntuple/USC.00000"$i".0001.A.storageManager.00.0000_TREE.root"
done > run1.log 2>&1&

for i in ` echo 757 758 760 762 763 766 769 768 770 771 773 775 776 777 778 779 781 782 790 788 `
do 
  echo $i
  cmsRun scripts/treeMaker_cfg.py "/afs/cern.ch/user/s/sroychow/public/sinpStorage/sroychow/May2016BeamTest/EDM/USC.00000"$i".0001.A.storageManager.00.0000.root" "/afs/cern.ch/user/s/sroychow/public/sinpStorage/sroychow/May2016BeamTest/Ntuple/USC.00000"$i".0001.A.storageManager.00.0000_TREE.root"
done > run2.log 2>&1&
