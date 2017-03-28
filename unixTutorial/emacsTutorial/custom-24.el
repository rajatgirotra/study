(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(c-basic-offset 4)
 '(c-default-style
   (quote
    ((c-mode . "linux")
     (c++-mode . "linux")
     (java-mode . "java")
     (awk-mode . "awk")
     (other . "gnu"))))
 '(calendar-week-start-day 1)
 '(column-number-mode t)
 '(frame-background-mode (quote dark))
 '(global-font-lock-mode t)
 '(global-linum-mode t)
 '(indent-tabs-mode nil)
 '(inhibit-default-init t)
 '(initial-frame-alist (quote ((fullscreen . maximized))))
 '(line-number-mode t)
 '(linum-format "%d ")
 '(save-abbrevs (quote silently))
 '(show-paren-delay 0)
 '(show-paren-mode t)
 '(standard-indent 4)
 '(tab-width 4))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :stipple nil :background "black" :foreground "white" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 113 :width normal :foundry "unknown" :family "DejaVu Sans Mono"))))
 '(popup-face ((t (:background "black" :foreground "white"))))
 '(popup-menu-selection-face ((t (:background "white" :foreground "black")))))


;;enable abbrev-mode by default
(setq-default abbrev-mode t)

;;Global Keybindings
(global-set-key "\C-xl" 'goto-line)
