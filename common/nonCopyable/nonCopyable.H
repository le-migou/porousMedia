#ifndef nonCopyable_H
#define nonCopyable_H

    struct
nonCopyable
{
    nonCopyable () = default;
    nonCopyable (nonCopyable const&) = delete;
};

#endif

