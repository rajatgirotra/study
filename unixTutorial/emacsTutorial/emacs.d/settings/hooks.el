
;; Enable ggtags when in C/C++ mode 
;; enable function to switch between c/c++ header and source file.
(add-hook 'c-mode-common-hook
   (lambda () (when (derived-mode-p 'c-mode 'c++-mode)
                (global-set-key (kbd "<backtab>") 'toggle-source-header)
                (if enable-ggtags
                   (ggtags-mode t)))))

;; Enable auto complete of C/C++ headers in C/C++mode.
(add-hook 'c++-mode-hook 'my:ac-c-headers-init)
(add-hook 'c-mode-hook 'my:ac-c-headers-init)

;; Add semantic as a backend when in C mode.
(add-hook 'c-mode-common-hook 'my:add-semantic-to-autocomplete)
