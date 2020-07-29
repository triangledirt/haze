;;(if cf-use-abbrevs (load "~/.emacs_ih_abbrevs"))

(global-set-key "\C-b" 'electric-buffer-list)
(global-set-key "\C-f" 'find-file)
(global-set-key "\C-j" 'indent-region)
(global-set-key "\C-t" 'goto-line)
(global-set-key "\C-v" 'other-window)
(global-set-key "\M-#" 'tags-query-replace)
(global-set-key "\M-s" 'tags-search)

(setq inhibit-startup-message 1)
(menu-bar-mode 0)
(setq transient-mark-mode t)
(global-font-lock-mode 0)
(normal-erase-is-backspace-mode 0)
(setq cf-use-abbrevs 't)
;; (add-hook 'c-mode-common-hook
;;           (lambda () (c-toggle-auto-hungry-state 1)))

(put 'downcase-region 'disabled nil)
(put 'upcase-region 'disabled nil)

(keyboard-translate ?\C-h ?\C-?)


(setq auto-mode-alist
      (append '(
                ("\\.php$" . c-mode)
                ("\\.js$" . c-mode)
                )
              auto-mode-alist))

(setq-default abbrev-mode 't)
(setq-default dabbrev-abbrev-char-regexp nil)
(setq-default indent-tabs-mode nil)
(setq-default require-final-newline 't)
(setq-default show-trailing-whitespace 't)
(setq-default show-ws-hard-space 't)

(add-hook 'c-mode-common-hook 'ih-c-mode-common-hook)

(add-hook 'c-mode-hook
          '(lambda ()
             (make-local-hook 'find-file-hooks)
             (make-local-hook 'write-contents-hooks)
             ;;(add-hook 'find-file-hooks 'indent-buffer)
             (add-hook 'write-contents-hooks 'delete-trailing-whitespace)
             (add-hook 'write-contents-hooks 'untabify-buffer)
             ;;(add-hook 'write-contents-hooks 'indent-buffer)
             )
          )

(defun ih-c-mode-common-hook ()
  (c-set-style "bsd")
  (c-set-offset 'arglist-cont-nonempty '++)
  (c-set-offset 'case-label '+)
  (setq c-basic-offset 2)
  (setq tab-width 2)
  )

(defun indent-buffer()
  (interactive)
  ""
  (save-excursion
    (mark-whole-buffer)
    (indent-region (point-min) (point-max)))
  nil)

(defun untabify-buffer()
  (interactive)
  "Untabify the current buffer.  Return nil.  Must return nil, if added to write-file-hooks."
  (save-excursion
    (goto-char (point-min))
    (while (re-search-forward "[ \t]+$" nil t)
      (delete-region (match-beginning 0) (match-end 0)))
    (goto-char (point-min))
    (if (search-forward "\t" nil t)
        (untabify (1- (point)) (point-max))))
  nil)
